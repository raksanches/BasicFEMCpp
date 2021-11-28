#include "BoundaryCondition.h"

BoundaryCondition::BoundaryCondition(const int& index, const int& nodeIndex, const std::vector<double>& componentX, const std::vector<double>& componentY,
                      const std::string& method, const std::string& referenceSystem, const double& penaltyParameter)
{
    index_ = index;
    nodeIndex_ = nodeIndex;
    componentX_ = componentX;
    componentY_ = componentY;
    method_ = method;
    referenceSystem_ = referenceSystem;
    penaltyParameter_ = penaltyParameter;
}
    
BoundaryCondition::BoundaryCondition(const int& index, const int& elementIndex, const int& elementSide, const std::vector<double>& componentX,
                      const std::vector<double>& componentY, const std::string& method, const std::string& referenceSystem, const double& penaltyParameter)
{
    index_ = index;
    elementIndex_ = elementIndex;
    elementSide_ = elementSide;
    componentX_ = componentX;
    componentY_ = componentY;
    method_ = method;
    referenceSystem_ = referenceSystem;
    penaltyParameter_ = penaltyParameter;
}

BoundaryCondition::~BoundaryCondition() {}

int BoundaryCondition::getNodeIndex()
{
    return nodeIndex_;
}

std::vector<double> BoundaryCondition::getComponent(const int& direction)
{
    if (direction == 0)
        return componentX_;
    else
        return componentY_;
    
}