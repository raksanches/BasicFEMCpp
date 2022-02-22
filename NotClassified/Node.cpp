#include "Node.h"

Node::Node(const int& index, const Vector2d& initialCoordinate)
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


 Vector2d Node::getCurrentCoordinate()
 {
     return currentCoordinate_;
 }


 void Node::setConstrain(const bool& isConstrained)
 {
     constrained_ = isConstrained;
 }

