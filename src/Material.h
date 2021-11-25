#pragma once

#include <string>

class Material
{
public:
	Material(const int& index, const double& elasticityModulus, const double& poisson);

	~Material();

	int getIndex();

	double getElasticityModulus();

	double getPoisson();

	void setIndex(const int& index);
	
	void setElasticityModulus(const double& poisson);

	void setPoisson(const double& elasticityModulus);

private:
	int index_;
	double elasticityMod_;
	double poisson_;
};

