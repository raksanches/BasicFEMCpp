#pragma once

#include <vector>
#include "Eigen/Dense"
using namespace Eigen;

class Node
{

public:
Node(const int& index, const Vector2d& initialCoordinate);


 int getIndex(); 

 double getDeltatxTimeStep(); 

 int getDOFNode(); 


 Vector2d getCurrentCoordinate(); 


 void setConstrain(const bool& isConstrained); 



private: 
 int index_; 
 Vector2d initialCoordinate_; 

 Vector2d currentCoordinate_; 

bool constrained_; 
int DOFNode_; 

};
