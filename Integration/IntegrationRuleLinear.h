#ifndef INTEGRATION_RULE_LINEAR
#define INTEGRATION_RULE_LINEAR

#include <cmath>
#include <stdio.h>
#include "IntegrationRule.h"

/*
    Class where the integration rules are defined
*/

class IntegrationRuleLinear : public IntegrationRule
{
protected:
    enum QuadratureType{GaussQuad, Other};//Other integration quadratures may be implemented.

private:
    //Quadrature type
    QuadratureType nQuadType = GaussQuad;

public:
    // Default Constructor
    IntegrationRuleLinear();
    
    // Constructor of an integration rule with specific polynomial order
    IntegrationRuleLinear(int order, QuadratureType qType = GaussQuad);
    
  
    // Dimension of the integration rule
    virtual int GetDimension() const override{
        return 1;
    }
    
    // Maximum order that can be exactly integrated by the Integration Rule
    virtual int MaximumOrder() const override{
        return 10;
    };
    
    // Set the polynomial order to be integrated by the integration rule
    virtual void SetOrder(int order) override;
    
    // Gauss Integration rule
    static void Gauss(const double x1, const double x2, MatrixXd &coord, VectorXd &weight);
};

#endif 