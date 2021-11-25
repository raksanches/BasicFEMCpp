#include "Element.h"
#include "../libs/tensorlib/tensor4.h"
#include "../libs/tensorlib/operators.h"

Element::Element(const int& index, const std::vector<Node*>& nodes, Material* material, const double& thickness, const std::string& elementType)
{
	index_ = index;
	nodes_ = nodes;
	material_ = material;
	thickness_ = thickness;
	elementType_ = elementType;
	order_ = 1;
}

Element::~Element() {}

int Element::getIndex()
{
	return index_;
}

Node* Element::getNode(const int& index)
{
	return nodes_[index];
}

std::vector<Node*> Element::getNodes()
{
	return nodes_;
}

std::string Element::getType()
{
	return elementType_;
}

std::vector<Node*> Element::getSideNodes(const int& side)
{
	std::vector<Node*> nodes; nodes.reserve(2);
	if (side == 0)
	{
		nodes.push_back(nodes_[0]); nodes.push_back(nodes_[1]);
	}
	else if (side == 1)
	{
		nodes.push_back(nodes_[1]); nodes.push_back(nodes_[2]);
	}
	else if (side == 2)
	{
		nodes.push_back(nodes_[2]); nodes.push_back(nodes_[0]);
	}
	return nodes;
}

