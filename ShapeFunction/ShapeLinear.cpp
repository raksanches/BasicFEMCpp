#include <cmath>
#include <math.h>
#include "ShapeLinear.h"


void ShapeLinear::Shape(VectorXd &xi, VectorXi &orders, VectorXd &phi, MatrixXd &dphi){
    
    if (orders[0] < 0 || orders[1] < 0 || orders[2] < 0) {
        std::cout << "Shape1d::Shape: Invalid dimension for arguments: order\n";
        PanicButton();
    }
    // if (orders[0] > 1 || orders[1] > 1) {
    //     std::cout << "Shape1d::Shape: Invalid dimension for arguments: order\n";
    //     PanicButton();
    // }
    if (orders[2] > 2) {
        std::cout << "Shape1d::Shape: Please implement it for order > 2\n";
        PanicButton();
    }
    
    auto nshape = NShapeFunctions(orders);
    phi.resize(nshape);
    dphi.resize(1,nshape);
    phi.setZero(); dphi.setZero();

    phi[0] = 0.5 * (1. - xi(0));
    phi[1] = 0.5 * (1. + xi(0));
    dphi(0,0) = -0.5;
    dphi(0,1) =  0.5;

    int count = 2;
    int is;
    for (is = 2; is < 3; is++) {
        if(orders[is] == 2){
            int is1 = SideNodeLocIndex(is, 0);
            int is2 = SideNodeLocIndex(is, 1);
            phi[is] = 4.*phi[is1] * phi[is2];
            dphi(0, is) = 4.*(dphi(0, is1) * phi[is2] + phi[is1] * dphi(0, is2));
            count++;
        } else if (orders[is] != 1) PanicButton();
    }

    if(count != nshape) PanicButton();
    for(int is = 3 ; is< nSides; is++) if(orders[is] != 1 && orders[is] != 2) PanicButton();
}

/// returns the number of shape functions associated with a side
int ShapeLinear::NShapeFunctions(int side, int order){

    if(order < 1 || order >10) PanicButton();
    switch (side)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 1;
        break;
    case 2:
        return order-1;
        break;
    
    default:
        std::cout << "Shape1d::NShapeFunctions : Wrong side " << side << "\n";
        PanicButton();
        return -1;
        break;
    }
    return -1;
}

/// returns the total number of shape functions
int ShapeLinear::NShapeFunctions(VectorXi &orders) {
    
    int nsf_tot = 0;
    for (int is=0; is<3; is++) {
        nsf_tot += NShapeFunctions(is, orders(is));
    }
    
    return nsf_tot;
}
