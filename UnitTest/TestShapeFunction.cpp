
#include <iostream>
#include <math.h>

#include "Eigen/Dense"
using namespace Eigen;

#include "IntegrationRuleLinear.h"
#include "ShapeLinear.h"


#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
using namespace Catch::literals;


using std::cout;
using std::endl;
using std::cin;


template<class shape>
void CheckLagrange(int order)
{
    IntegrationRuleLinear integ;
    integ.SetOrder(10);

    auto nshape = shape::NShapeFunctions(order);
    double Tol = 1.e-10;

    for (int i = 0; i < integ.NPoints(); i++)
    {
        MatrixXd coord(1,1);
        double weig = 0.;
        integ.Point(i,coord,weig);
        // std::cout << "Point " << i << "; Coord = " << coord << " , Weight = " << weig << std::endl; 

        VectorXd phi;
        MatrixXd DPhi;
        VectorXd xi(1);
        xi(0) = coord(0,0);
        
        shape::Shape(xi,order,phi,DPhi,SLagrange);
        // std::cout <<"Shape = \n" << phi << " , \n DShape = \n" << DPhi << std::endl;

        double sumPhi = 0.;
        double sumDPhi = 0.;
        for (int ishape = 0; ishape < nshape; ishape++){
            sumPhi += phi(ishape);
            sumDPhi += DPhi(0,ishape);
        }
    
        REQUIRE(fabs(sumPhi - 1.) < Tol);
        REQUIRE(fabs(sumDPhi) < Tol);
    }   
}


template<class shape>
void CheckChebyshev(int order)
{
    IntegrationRuleLinear integ;
    integ.SetOrder(order+order);

    auto nshape = shape::NShapeFunctions(order);

    MatrixXd stiff(nshape,nshape);
    MatrixXd mass(nshape,nshape);
    stiff.setZero();
    mass.setZero();

    for (int i = 0; i < integ.NPoints(); i++)
    {
        MatrixXd coord(1,1);
        double weig = 0.;
        integ.Point(i,coord,weig);
        // std::cout << "Point " << i << "; Coord = " << coord << " , Weight = " << weig << std::endl; 

        VectorXd phi;
        MatrixXd DPhi;
        VectorXd xi(1);
        xi(0) = coord(0,0);
        
        shape::Shape(xi,order,phi,DPhi,SChebyshev);
        // std::cout <<"Shape = \n" << phi << " , \n DShape = \n" << DPhi << std::endl;

        for (int i = 0; i < nshape; i++){
            for (int j = 0; j < nshape; j++){
                mass(i,j) += phi(i)*phi(j)*weig;
                stiff(i,j) += DPhi(0,i)*DPhi(0,j)*weig;
            }
        }
    }//Integration
    // std::cout << "Mass (" << order << ") =\n " << mass << std::endl;
    // std::cout << "Stiff (" << order << ") =\n " << stiff << std::endl;
}

TEST_CASE("shape_test","[functionspace]")
{
    
    SECTION("LagrangeShape")
    {
        for (int i = 1; i < 11; i++)
        {
            CheckLagrange<ShapeLinear>(i);
        }
    }

    SECTION("ChebyshevShape")
    {
        for (int i = 1; i < 11; i++)
        {
            CheckChebyshev<ShapeLinear>(i);
        }
    }
    
}
