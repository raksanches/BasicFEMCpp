#include "PlaneSurface.h"



PlaneSurface::PlaneSurface() {}

PlaneSurface::PlaneSurface(const int& index, const std::string& name, LineLoop* lineLoop, const double& thickness)
{
	index_ = index;
	name_ = name;
	lineLoop_ = lineLoop;
	thickness_ = thickness;
}

PlaneSurface::~PlaneSurface() {}

int PlaneSurface::getIndex()
{
	return index_;
}

std::string PlaneSurface::getName()
{
	return name_;
}

LineLoop* PlaneSurface::getLineLoop()
{
	return lineLoop_;
}

Material* PlaneSurface::getMaterial()
{
	return material_;
}

double PlaneSurface::getThickness()
{
	return thickness_;
}

std::vector<Element*> PlaneSurface::getElements()
{
	return elements_;
}

void PlaneSurface::setMaterial(Material* material)
{
	material_ = material;
}

void PlaneSurface::setThickness(const double& thickness)
{
	thickness_ = thickness;
}

void PlaneSurface::addElementToSurface(Element* object)
{
	elements_.push_back(object);
}

std::string PlaneSurface::getGmshCode()
{
	std::stringstream text;
	text << name_ << " = news; Plane Surface(" << name_ << ") = {" << lineLoop_->getName() << "}; Physical Surface('" << name_ << "') = {" << name_ << "};\n//\n";
	return text.str();
}