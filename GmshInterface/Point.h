#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Node.h"

class Point
{
public:
	Point();

	Point(const int& index,
		const std::string& name,
		const std::vector<double>& coordinates,
		const double& lcar,
		const bool& discretization = true);

	~Point();

	int getIndex();

	std::string getName();

	double getX();

	double getY();

	std::vector<double> getCoordinates();

	double getLcar();

	bool getDiscretization();

	Node* getPointNode();

	std::string getGmshCode();

	void setIndex(const int& index);

	void setName(const std::string& name);

	void setX(const double& x);

	void setY(const double& y);

	void setLcar(const double& lcar);

	void setDiscretization(const bool& discretization);

	void addNodeToPoint(Node* node);

private:
	int index_;           					// Point index
	std::string name_;    					// Gmsh Physical entity name
	std::vector<double> coordinates_;   	// Coordinates vector (x,y)
	double lcar_; 							// Characteristic length Gmsh parameter
	bool discretization_; 					// Choose to discretize a point with a mesh node
	Node* pointNode_;     					// Defines the mesh node discretizing the point
};
