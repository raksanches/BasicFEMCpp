#ifndef GEOMETRIC_ELEMENT_T
#define GEOMETRIC_ELEMENT_T

#include "GeometricElement.h"
#include "GeometricMesh.h"
#include "DenseEigen.h"

template<class Geometry>
class GeometricElementT : public GeometricElement
{
private:

    Geometry    fGeom;
    
public:
    //Default constructor
    GeometricElementT(){};

    GeometricElementT(const VecInt &nodeindices, int matid, GeometricMesh* gmesh, int index);

    ~GeometricElementT(){};
};




#endif