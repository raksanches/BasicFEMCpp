#pragma once

#include <string>
#include <vector>

class GeometricBoundaryCondition
{
public:
	GeometricBoundaryCondition(const int& index, const std::string& object, const std::vector<double>& componentX = std::vector<double>(), const std::vector<double>& componentY = std::vector<double>(), const std::string& referenceSystem = "GLOBAL", const std::string& method = "STRONG", const double& penaltyParameter = 1.0e6);

	~GeometricBoundaryCondition();

	int getIndex();

	std::string getPointName();

	std::string getLineName();

	std::string getReferenceSystem();

	std::vector<double> getComponentX();

	std::vector<double> getComponentY();

	std::string getMethod();

	double getPenaltyParameter();

	void setIndex(const int& index);

	void setPointName(const std::string& name);

	void setLineName(const std::string& name);

	void setReferenceSystem(const std::string& referenceSystem);

	void setComponentX(std::vector<double> componentX);

	void setComponentY(std::vector<double> componentY);

	void setMethod(const std::string& methhod);

	void setPenaltyParameter(const double& penaltyParameter);

private:
	int index_;
	std::string point_;
	std::string line_;
	std::string referenceSystem_;
	std::vector<double> componentX_;
	std::vector<double> componentY_;
	std::string method_;
	double penaltyParameter_;

};

