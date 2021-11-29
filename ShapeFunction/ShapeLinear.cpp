#include <cmath>
#include <math.h>
#include "ShapeLinear.h"


void ShapeLinear::Shape(VectorXd &xi, int &pOrder, VectorXd &phi, MatrixXd &dphi, ShapeType sType){
    
    if (pOrder < 1 || pOrder > 10) {
        std::cout << "ShapeLinear::Shape: Invalid polynomial order\n";
        PanicButton();
    }
    
    int nshape = NShapeFunctions(pOrder);
    phi.resize(nshape);
    dphi.resize(1,nshape);
    phi.setZero(); dphi.setZero();

    phi[0] = 0.5 * (1. - xi(0));
    phi[1] = 0.5 * (1. + xi(0));
    dphi(0,0) = -0.5;
    dphi(0,1) =  0.5;

    switch (sType){
        case SLagrange:
            Lagrange(xi,pOrder,phi,dphi);
            break;
        case SChebyshev:
            Chebyshev(xi,pOrder,phi,dphi);
            break;
        case SLegendre:
            PanicButton();
            // Legendre(xi,pOrder,phi,dphi);
            break;
        default:
            break;
    }
    
}

/// returns the number of shape functions associated with a side
int ShapeLinear::NShapeFunctions(int order){
    if(order < 1 || order >10) PanicButton();
    return order + 1;
}

// Lagrange polynomials
void ShapeLinear::Lagrange(VectorXd &xi, int &pOrder, VectorXd &phi, MatrixXd &dphi){
    double aux;
    int nshape = NShapeFunctions(pOrder);
    VectorXd AdimCoord(nshape);
    double dist = 2./double(nshape - 1);
    for (int i = 0; i < nshape; i++){
        AdimCoord(i) = -1. + double(i)*dist;
    }

    for (int j=0; j<nshape; j++) {
        phi(j) = 1.;
        dphi(0,j) = 0.;
        for (int i = 0; i < nshape; i++) {
            aux = 1.;
            if(i != j){
                phi(j) = phi(j)*(xi(0)-AdimCoord(i))/(AdimCoord(j)-AdimCoord(i));
                for (int k=0; k<nshape; k++) {
                    if ((i != k) && (j != k)) aux = aux*(xi(0)-AdimCoord(k));
                };
                dphi(0,j) += aux;
            };
        };
    };

    for (int i=0; i<nshape; i++) {
        for (int k=0; k<nshape; k++) {
            if (i != k) dphi(0,i) /= (AdimCoord(i)-AdimCoord(k));
        };
    };
}

// Chebyshev polynomials
void ShapeLinear::Chebyshev(VectorXd &xi, int &pOrder, VectorXd &phi, MatrixXd &dphi){

    int nshape = NShapeFunctions(pOrder);
    VectorXd phiChebyshev(nshape);
    VectorXd DPhiChebyshev(nshape);
    phiChebyshev(0) = 1.;
    phiChebyshev(1) = xi(0);
    DPhiChebyshev(0) = 0.;
    DPhiChebyshev(1) = 1.;

    for (int i = 2; i < nshape; i++){
        phiChebyshev(i) = 2. * xi(0) * phiChebyshev(i-1) - phiChebyshev(i-2);
        DPhiChebyshev(i) = 2. * xi(0) * DPhiChebyshev(i-1) + 2.*phiChebyshev(i-1) - DPhiChebyshev(i-2);
    }

    for (int i = 2; i < nshape; i++){
        phi(i) = 4. * phi(0) * phi(1) * phiChebyshev(i-2);
        dphi(0,i) = 4. * (dphi(0,0) * phi(1) * phiChebyshev(i-2) +
                          phi(0) * dphi(0,1) * phiChebyshev(i-2) +
                          phi(0) * phi(1) * DPhiChebyshev(i-2));//Chain rule on phi expression
    }
    // std::cout << "DPhi cheby = " << xi(0) << "\n \n " << DPhiChebyshev << std::endl;
    // std::cout << "DPhi = " << xi(0) << "\n \n " << dphi << std::endl;
   
}