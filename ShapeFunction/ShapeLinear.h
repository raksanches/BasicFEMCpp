#ifndef SHAPE_FUNCTION_LINEAR
#define SHAPE_FUNCTION_LINEAR

#include "TopologyLinear.h"
#include "ShapeTypes.h"

/**
 * Shape functions for line elements
 */
class ShapeLinear : public TopologyLinear
{

public:
    // Computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
    static void Shape(VectorXd &xi, int &pOrder, VectorXd &phi, MatrixXd &dphi, ShapeType stype = SLagrange);
    
    // Returns the number of shape functions associated with a side
    static int NShapeFunctions(int order);

    // Lagrange polynomials
    static void Lagrange(VectorXd &xi, int &pOrder, VectorXd &phi, MatrixXd &dphi);

    // Orthogonal Chebyshev polynomials
    static void Chebyshev(VectorXd &xi, int &pOrder, VectorXd &phi, MatrixXd &dphi);

    // Orthogonal Legendre polynomials
    static void Legendre(VectorXd &xi, int &pOrder, VectorXd &phi, MatrixXd &dphi);

};

#endif 
