#include "GeometricNode.h"

GeometricNode::GeometricNode(VecDouble &coord, int64_t &index){
    fCoordinates.resize(3);
    fCoordinates = coord;
    fIndex = index;
}

void GeometricNode::SetCoordinates(VecDouble &coord){
    
#ifdef LIBDEBUG
    if (fCoordinates.size() != 3){
        fCoordinates.resize(3);
    }
#endif
    fCoordinates = coord;
}

void GeometricNode::SetIndex(int64_t &index){
    fIndex = index;
}