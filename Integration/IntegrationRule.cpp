
#include "IntegrationRule.h"

#include <iostream> 
#include <vector> 
#include <cmath>
#include <iomanip>

using namespace std;
IntegrationRule::IntegrationRule() : nPoint(), nWeight(){
    nOrder = 0;
}

IntegrationRule::IntegrationRule(int order) {
    nOrder = order;
}

IntegrationRule::~IntegrationRule() {

}

IntegrationRule::IntegrationRule(const IntegrationRule& copy) {
    nOrder = copy.nOrder;
    nPoint = copy.nPoint;
    nWeight = copy.nWeight;
}

IntegrationRule &IntegrationRule::operator=(const IntegrationRule &cp) {
    nOrder = cp.nOrder;
    nPoint = cp.nPoint;
    nWeight = cp.nWeight;
    return *this;
}

int IntegrationRule::NPoints() const {
    return nWeight.size();
}

void IntegrationRule::Point(int p, MatDouble &coord, double &weight) const {
    int dim = 1;//coord.size();

    for (int i = 0; i < dim; i++) {
        coord(i) = nPoint(p,i);
    }
    weight = nWeight(p);
}