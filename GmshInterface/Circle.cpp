#include "Circle.h"

Circle::Circle(const int& index, const std::string& name, std::vector<Point*> points, const bool& discretization)
{
    index_ = index;
	name_ = name;
	discretization_ = discretization;
	points_.reserve(3);
	for (Point* point : points)
		points_.push_back(point);
}

Circle::~Circle() {}

Circle* Circle::operator-()
{
	Circle* copy = new Circle(index_, name_, {points_});
	copy->setName("-" + name_);
	return copy;
}

std::string Circle::getGmshCode()
{
    std::stringstream text;
	if (discretization_) {
		text << name_ << " = newl; Circle(" << name_ << ") = {" << points_[0]->getName() << ", " << points_[1]->getName() << ", " << points_[2]->getName()
				<< "}; Physical Line('" << name_ << "') = {" << name_ << "};\n//\n";
		return text.str();
	}
	else {
		text << name_ << " = newl; Circle(" << name_ << ") = {" << points_[0]->getName() << ", " << points_[1]->getName() << ", " << points_[2]->getName()
				<< "};\n//\n";
		return text.str();
	}
}

Point* Circle::getMiddlePoint()
{
    return points_[1];
}