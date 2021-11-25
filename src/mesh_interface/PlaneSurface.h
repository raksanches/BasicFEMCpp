#pragma once

#include "LineLoop.h"
#include "../Material.h"

class PlaneSurface
{
public:
	PlaneSurface();

	PlaneSurface(const int& index, const std::string& name, LineLoop* lineLoop, const double& thickness = 1.0);

	~PlaneSurface();

	int getIndex();

	std::string getName();

	LineLoop* getLineLoop();

	Material* getMaterial();

	double getThickness();

	std::vector<Element*> getElements();

	void setMaterial(Material* material);

	void setThickness(const double& thickness);

	void addElementToSurface(Element* object);

	std::string getGmshCode();

private:
	int index_;
	std::string name_;
	double thickness_;
	LineLoop* lineLoop_;
	Material* material_;
	std::vector<Element*> elements_;
};

