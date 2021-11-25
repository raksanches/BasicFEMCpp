#pragma once

#include <vector>
#include <string>

class BoundaryCondition
{
    public:
    BoundaryCondition(const int& index, const int& nodeIndex, const std::vector<double>& componentX, const std::vector<double>& componentY,
                      const std::string& method, const std::string& referenceSystem, const double& penaltyParameter = 1.0e6);
    
    BoundaryCondition(const int& index, const int& elementIndex, const int& elementSide, const std::vector<double>& componentX,
                      const std::vector<double>& componentY, const std::string& method, const std::string& referenceSystem, const double& penaltyParameter = 1.0e6);

    ~BoundaryCondition();

    int getNodeIndex();

    std::vector<double> getComponent(const int& direction);

    private:
    int index_;
    int nodeIndex_;
    int elementIndex_;
    int elementSide_;
    std::vector<double> componentX_;
	std::vector<double> componentY_;
    std::string method_;
    double penaltyParameter_;
    std::string referenceSystem_;

};