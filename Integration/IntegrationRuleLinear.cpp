
#include "IntegrationRuleLinear.h"
#include "PanicButton.h"

#include <iostream> 
#include <vector> 
#include <cmath>
#include <iomanip>

IntegrationRuleLinear::IntegrationRuleLinear(){

}

IntegrationRuleLinear::IntegrationRuleLinear(int order, QuadratureType qType) : nQuadType(qType) {
    SetOrder(order);
}

void IntegrationRuleLinear::SetOrder(int order) {
    if ((order < 0) || (order > MaximumOrder())) PanicButton();
    nOrder = order;
    
    int np = 0;

    switch (nQuadType) {
        case GaussQuad:
            //Compute number of integration points and resize vectors and matrices
            np = (nOrder+2)/2;
            nPoint.resize(np,GetDimension());
            nWeight.resize(np);
            Gauss(-1,1,nPoint,nWeight);
            break;
        case Other:
            PanicButton();
        break;
    default:
        PanicButton();
        break;
    }
}

void IntegrationRuleLinear::Gauss(const double x1, const double x2, MatrixXd &coord, VectorXd &weight){
    int n = weight.size();

    double EPS = 1.0e-14;
    int m, j, i;
    double z1, z, xm, xl, pp, p3, p2, p1;    
    
    m = (n + 1) / 2;
    xm = 0.5 * (x2 + x1);
    xl = 0.5 * (x2 - x1);
    for (i = 0; i < m; i++) {
        z = cos(M_PI * (i + 0.75) / (n + 0.5));
        do {
            p1 = 1.0;
            p2 = 0.0;
            for (j = 0; j < n; j++) {
                p3 = p2;
                p2 = p1;
                p1 = ((2.0 * j + 1.0) * z * p2 - j * p3) / (j + 1);
            }
            pp = n * (z * p1 - p2) / (z * z - 1.0);
            z1 = z;
            z = z1 - p1 / pp;
        } while (fabs(z - z1) > EPS);
        coord(i) = xm - xl*z;
        coord(n - 1 - i) = xm + xl*z;
        weight(i) = 2.0 * xl / ((1.0 - z * z) * pp * pp);
        weight(n - 1 - i) = weight(i);
    }
    
}