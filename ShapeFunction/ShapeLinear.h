#ifndef SHAPE_FUNCTION_LINEAR
#define SHAPE_FUNCTION_LINEAR

#include "TopologyLinear.h"

/**
 * Shape functions for line elements
 */
class ShapeLinear : public TopologyLinear
{
public:
    // Computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
    static void Shape(VectorXd &xi, VectorXi &orders, VectorXd &phi, MatrixXd &dphi);
    
    // Returns the number of shape functions associated with a side
    static int NShapeFunctions(int side, int order);
    
    // Returns the total number of shape functions
    static int NShapeFunctions(VectorXi &orders);

};

#endif 
