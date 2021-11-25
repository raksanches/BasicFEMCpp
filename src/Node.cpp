#include "Node.h"

Node::Node(const int& index, const bounded_vector<double, 2>& initialCoordinate)
{
    index_ = index;
    initialCoordinate_ = initialCoordinate;
    currentCoordinate_ = initialCoordinate;

}


 int Node::getDOFNode()
 {
     return DOFNode_;
 }


int Node::getIndex()
{
    return index_;
}


 bounded_vector<double, 2> Node::getCurrentCoordinate()
 {
     return currentCoordinate_;
 }


 void Node::setConstrain(const bool& isConstrained)
 {
     constrained_ = isConstrained;
 }

