#ifndef SHAPE_FUNCTION_LINEAR
#define SHAPE_FUNCTION_LINEAR

#include "TopologyLine.h"
#include "ShapeTypes.h"

/**
 * Shape functions for line elements
 */
class ShapeLinear : public TopologyLine
{

public:
    // Computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
    static void Shape(VecDouble &xi, int &pOrder, VecDouble &phi, MatDouble &dphi, ShapeType stype = SLagrange);
    
    // Returns the number of shape functions associated with a side
    static int NShapeFunctions(int order);

    // Lagrange polynomials
    static void Lagrange(VecDouble &xi, int &pOrder, VecDouble &phi, MatDouble &dphi);

    // Orthogonal Chebyshev polynomials
    static void Chebyshev(VecDouble &xi, int &pOrder, VecDouble &phi, MatDouble &dphi);

    // Orthogonal Legendre polynomials
    static void Legendre(VecDouble &xi, int &pOrder, VecDouble &phi, MatDouble &dphi);

};

#endif 
