#include "Line.h"

Line::Line() {}

Line::Line(const int& index, const std::string& name, std::vector<Point*> points, const bool& discretization)
{
	index_ = index;
	name_ = name;
	discretization_ = discretization;
	points_.reserve(2);
	for (Point* point : points)
		points_.push_back(point);
}

Line::~Line() {}

Line* Line::operator-()
{
//    if(name_[0] == '-') {
//	Line* copy = this;
//	copy->setName(name_.erase(0));
//	return *copy;
//    } else {
//	Line* copy = this;
//	copy->setName(name_.insert(0, "-"));
//	return *copy;
//    }
	Line* copy = new Line(index_, name_, {points_});
	copy->setName("-" + name_);
	return copy;
}

int Line::getIndex()
{
	return index_;
}
std::string Line::getName()
{
	return name_;
}
Point* Line::getInitialPoint()
{
	return points_[0];
}
Point* Line::getEndPoint()
{	
	int last = points_.size() -1;
	return points_[last];
}
bool Line::getDiscretization()
{
	return discretization_;
}
std::vector<Node*> Line::getLineNodes()
{
	return lineNodes_;
}
std::string Line::getGmshCode()
{
	std::stringstream text;
	if (discretization_) {
		text << name_ << " = newl; Line(" << name_ << ") = {" << points_[0]->getName() << ", " << points_[1]->getName()
			<< "}; Physical Line('" << name_ << "') = {" << name_ << "};\n//\n";
		return text.str();
	}
	else {
		text << name_ << " = newl; Line(" << name_ << ") = {" << points_[0]->getName() << ", " << points_[1]->getName()
			<< "};\n//\n";
		return text.str();
	}
}
void Line::setIndex(const int& index)
{
	index_ = index;
}
void Line::setName(const std::string& name)
{
	name_ = name;
}
void Line::setInitialPoint(Point& point)
{
	//points_[0] = point;
}
void Line::setEndPoint(Point& point)
{
	//points_[1] = point;
}
void Line::setDiscretization(const bool& discretization)
{
	discretization_ = discretization;
}
void Line::appendNodes(std::vector<Node*> nodes)
{
	for (Node* node1 : nodes)
	{
		bool notDuplicate = true;
		for (Node* node2 : lineNodes_)
		{
			if (node1->getIndex() == node2->getIndex())
			{
				notDuplicate = false;
				break;
			}
		}
		if (notDuplicate)
			lineNodes_.push_back(node1);
	}
}
void Line::appendPlaneElement(Element* element)
{
	int numberOfSides;
	(element->getType()[0] == 'T') ? numberOfSides = 3 : numberOfSides = 4;

	std::vector<std::vector<Node*> > sidesNodes; sidesNodes.reserve(6);
	for (int i = 0; i < numberOfSides; i++)
	{	
		sidesNodes.push_back(element->getSideNodes(i));
	}
	//Verifying which element side touches the line
	// for (std::vector<Node*> nodes1 : lineNodes_)
	// {
	// 	int side = 0;
	// 	for (std::vector<Node*> nodes2 : sidesNodes)
	// 	{
	// 		if (nodes1 == nodes2)
	// 		{
	// 			lineElements_.first.push_back(element);
	// 			lineElements_.second.push_back(side);
	// 			break;
	// 		}
	// 		side++;
	// 	}
	// }

	for (int side = 0; side < numberOfSides; side++)
	{
		std::vector<int> nodeCoincident(sidesNodes[side].size(), 0);
		int i = 0;
		for (Node* node1 : sidesNodes[side])
		{
			for (Node* node2 : lineNodes_)
			{
				if (node1->getIndex() == node2->getIndex())
					{
						nodeCoincident[i] = 1;
						break;
					}
			}
			i++;
		}
		int sum = 0;
		for (int j = 0; j < nodeCoincident.size(); j++)
			sum += nodeCoincident[j];
		if (sum == nodeCoincident.size())
		{
			lineElements_.first.push_back(element);
 			lineElements_.second.push_back(side);
		}
	}
}