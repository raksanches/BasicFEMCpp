#pragma once

#include "Line.h"
#include "Circle.h"
#include "Spline.h"

class LineLoop
{
public:
	LineLoop();

	LineLoop(const int& index, const std::string& name, std::vector<Line*> lines);

	~LineLoop();

	int getIndex();

	std::string getName();

	Line* getLine(const int& index);

	std::vector<Line*> getLines();

	std::string getGmshCode();

	void setIndex(const int& index);

	void setName(const std::string& name);

	void verification();

private:
	int index_;
	std::string name_;
	std::vector<Line*> lines_;
};

