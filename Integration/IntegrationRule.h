#ifndef INTEGRATION_RULE
#define INTEGRATION_RULE

#include <cmath>
#include <stdio.h>
#include "DenseEigen.h"

/*
    Class where the integration rules are defined
*/

class IntegrationRule
{
protected:
    // Polynomial order to be integrated
    int nOrder;
    
    // Integration rule points
    MatDouble nPoint;
    
    // Weight of the integration point
    VecDouble nWeight;

public:
  
    // Default Constructor
    IntegrationRule();
    
    // Constructor of an integration rule with specific polynomial order
    IntegrationRule(int order);
    
    // Destructor of an integration rule
    virtual ~IntegrationRule();
    
    // Operator of copy of an integration rule
    virtual IntegrationRule &operator=(const IntegrationRule &copy);
    
    // Copy constructor of integration rule
    IntegrationRule(const IntegrationRule &copy);
    
    // Dimension of the integration rule
    virtual int GetDimension() const = 0;
    
    // Maximum order that can be exactly integrated by the Integration Rule
    virtual int MaximumOrder() const = 0;
    
    // Set the polynomial order to be integrated by the integration rule
    virtual void SetOrder(int order)
    {
        nOrder=order;
    }
    
    // Get polynomial order of the integration rule
    virtual int GetOrder() const
    {
        return nOrder;
    }
    
    // Return the number of integration points
    virtual int NPoints() const;
    
    // Function returning coordinates and weights of the integration points
    virtual void Point(int p, MatDouble &coord, double &weight) const;
    
};

#endif 