#pragma once

#include "Point.h"
#include "Element.h"

class Line
{
public:
	Line();

	Line(const int& index, const std::string& name, std::vector<Point*> points, const bool& discretization = true);

	~Line();

	Line* operator-();

	int getIndex();

	std::string getName();

	Point* getInitialPoint();

	Point* getEndPoint();

	bool getDiscretization();

	std::vector<Node*> getLineNodes();

	std::string virtual getGmshCode();

	void setIndex(const int& index);

	void setName(const std::string& name);

	void setInitialPoint(Point& point);

	void setEndPoint(Point& point);

	void setDiscretization(const bool& discretization);

	void appendNodes(std::vector<Node*> nodes);

	void appendPlaneElement(Element* element);

protected:
	int index_;
	std::string name_;
	std::vector<Point*> points_;
	bool discretization_;
	std::vector<Node*> lineNodes_;
	std::pair<std::vector<Element*>, std::vector<int> > lineElements_;
};

