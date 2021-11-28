#pragma once

#include "Node.h"
#include "Material.h"
#include <tuple>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

class Element
{
public:
	Element(const int& index, const std::vector<Node*>& nodes, Material* material, const double& thickness, const std::string& elementType);

	~Element();

	int getIndex();

	Node* getNode(const int& index);

	std::vector<Node*> getNodes();

	std::string getType();

	std::vector<Node*> getSideNodes(const int& side);

	
private:
	int index_;
	int order_;
	std::vector<Node*> nodes_;
	Material* material_;
	double thickness_;
	std::string elementType_;
	double area_;
};

