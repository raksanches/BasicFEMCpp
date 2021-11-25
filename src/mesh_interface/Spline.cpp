#include "Spline.h"

Spline::Spline(const int& index, const std::string& name, std::vector<Point*> points, const bool& discretization)
{
    index_ = index;
	name_ = name;
	discretization_ = discretization;
	points_.reserve(points.size());
	for (Point* point : points)
		points_.push_back(point);
}

Spline::~Spline() {}

Spline* Spline::operator-()
{
    Spline* copy = new Spline(index_, name_, {points_});
	copy->setName("-" + name_);
	return copy;
}

std::string Spline::getGmshCode()
{
    std::stringstream text;
	if (discretization_) {
		text << name_ << " = newl; Spline(" << name_ << ") = {";
        int cont = 0;
		for (Point* p : points_)
		{
			text << p->getName();
			if (cont != (points_.size() - 1))
				text << ", ";
			cont += 1;
		}
		text << "}; Physical Line('" << name_ << "') = {" << name_ << "};\n//\n";
		return text.str();	
	}
	else {
		text << name_ << " = newl; Spline(" << name_ << ") = {";
        int cont = 0;
		for (Point* p : points_)
		{
			text << p->getName();
			if (cont != (points_.size() - 1))
				text << ", ";
			cont += 1;
		}
		text << "};\n//\n";
		return text.str();	
	}
}