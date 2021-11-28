#include "GeometricBoundaryCondition.h"

GeometricBoundaryCondition::GeometricBoundaryCondition(const int& index,
	const std::string& object,
	const std::vector<double>& componentX,
	const std::vector<double>& componentY,
	const std::string& referenceSystem,
	const std::string& method,
	const double& penaltyParameter)
{
	index_ = index;
	(object[0] == 'p') ? point_ = object : line_ = object;
	componentX_ = componentX;
	componentY_ = componentY;
	referenceSystem_ = referenceSystem;
	method_ = method;
	penaltyParameter_ = penaltyParameter;
}

GeometricBoundaryCondition::~GeometricBoundaryCondition() {}

int GeometricBoundaryCondition::getIndex()
{
	return index_;
}

std::string GeometricBoundaryCondition::getPointName()
{
	return point_;
}

std::string GeometricBoundaryCondition::getLineName()
{
	return line_;
}

std::string GeometricBoundaryCondition::getReferenceSystem()
{
	return referenceSystem_;
}

std::vector<double> GeometricBoundaryCondition::getComponentX()
{
	return componentX_;
}

std::vector<double> GeometricBoundaryCondition::getComponentY()
{
	return componentY_;
}

std::string GeometricBoundaryCondition::getMethod()
{
	return method_;
}

double GeometricBoundaryCondition::getPenaltyParameter()
{
	return penaltyParameter_;
}

void GeometricBoundaryCondition::setIndex(const int& index)
{
	index_ = index;
}

void GeometricBoundaryCondition::setPointName(const std::string& name)
{
	point_ = name;
}

void GeometricBoundaryCondition::setLineName(const std::string& name)
{
	line_ = name;
}

void GeometricBoundaryCondition::setReferenceSystem(const std::string& referenceSystem)
{
	referenceSystem_ = referenceSystem;
}

void GeometricBoundaryCondition::setComponentX(std::vector<double> componentX)
{
	componentX_ = componentX;
}

void GeometricBoundaryCondition::setComponentY(std::vector<double> componentY)
{
	componentY_ = componentY;
}

void GeometricBoundaryCondition::setMethod(const std::string& method)
{
	method_ = method;
}

void GeometricBoundaryCondition::setPenaltyParameter(const double& penaltyParameter)
{
	penaltyParameter_ = penaltyParameter;
}
