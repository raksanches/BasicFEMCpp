
#include <iostream>
#include <math.h>

#include "IntegrationRuleLinear.h"
#include "ShapeLinear.h"


#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
using namespace Catch::literals;


using std::cout;
using std::endl;
using std::cin;


template<class shape>
void CheckShape(int order)
{
    IntegrationRuleLinear integ;
    integ.SetOrder(order);

    VectorXi orders;
    orders.resize(3);
    orders.fill(order);
    auto nshape = shape::NShapeFunctions(orders);
    double Tol = 1.e-10;

    // std::cout << integ.NPoints() << std::endl;
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
        
        shape::Shape(xi,orders,phi,DPhi);
        // std::cout <<"Shape = \n" << phi << " , \n DShape = \n" << DPhi << std::endl;

        double sumPhi = 0.;
        double sumDPhi = 0.;
        for (int ishape = 0; ishape < 2; ishape++){
            sumPhi += phi(ishape);
        }
    
        REQUIRE(fabs(sumPhi - 1.) < Tol);
    }

    
    
}
TEST_CASE("shape_test","[functionspace]")
{
    
    SECTION("ShapeLinear")
    {
        CheckShape<ShapeLinear>(1);
        CheckShape<ShapeLinear>(2);
    }
    
}
