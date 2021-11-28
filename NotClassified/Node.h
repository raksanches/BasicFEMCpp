#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <vector>

using namespace boost::numeric::ublas;

class Node
{

public:
Node(const int& index, const bounded_vector<double, 2>& initialCoordinate);


 int getIndex(); 

 double getDeltatxTimeStep(); 

 int getDOFNode(); 


 bounded_vector<double, 2> getCurrentCoordinate(); 


 void setConstrain(const bool& isConstrained); 



private: 
 int index_; 
 bounded_vector<double, 2> initialCoordinate_; 

 bounded_vector<double, 2> currentCoordinate_; 

bool constrained_; 
int DOFNode_; 

};
