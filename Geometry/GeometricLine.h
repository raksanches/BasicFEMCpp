#ifndef GEOMETRIC_LINE
#define GEOMETRIC_LINE

#include "TopologyLine.h"

class GeometricLine : public TopologyLine
{
public:
    GeometricLine(){};

    ~GeometricLine(){};

    // Set the node indices of the element
    void SetNodes(const VecInt &nodes);

protected:
    // Indexes of the nodes of the geometry
	VecInt fNodeIndices;

};



#endif
