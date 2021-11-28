#include "Material.h"

Material::Material(const int& index, const double& elasticityModulus, const double& poisson)
{
	index_ = index;
	elasticityMod_ = elasticityModulus;
	poisson_ = poisson;
}

Material::~Material() {}

int Material::getIndex()
{
	return index_;
}

double Material::getElasticityModulus()
{
	return elasticityMod_;
}

double Material::getPoisson()
{
	return poisson_;
}

void Material::setIndex(const int& index)
{
	index_ = index;
}

void Material::setElasticityModulus(const double& elasticityModulus)
{
	elasticityMod_ = elasticityModulus;
}

void Material::setPoisson(const double& poisson)
{
	poisson_ = poisson;
}
