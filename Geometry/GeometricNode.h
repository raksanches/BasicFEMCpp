#ifndef GEOMETRIC_NODE
#define GEOMETRIC_NODE

#include <iostream>
#include "DenseEigen.h"

class GeometricNode
{
private:
    VecDouble fCoordinates;
    int64_t   fIndex;

public:
    //Default constructor
    GeometricNode(){};

    GeometricNode(VecDouble &coord, int64_t &index);

    //Default destructor
    ~GeometricNode(){};

    void SetCoordinates(VecDouble &coord);

    VecDouble &GetCoordinates() {
        return fCoordinates;
    }

    void SetIndex(int64_t &index);

    int64_t &GetIndex(){
        return fIndex;
    }
};

#endif
