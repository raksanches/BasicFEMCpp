#ifndef GEOMETRIC_MESH
#define GEOMETRIC_MESH


#include "GeometricMap.h"
#include "GeometricNode.h"
#include "GeometricElement.h"

class GeometricMesh
{
private:
    GeometricMap fGeoMap;

    std::vector<GeometricNode> fNodes;

    std::vector<GeometricElement *> fElements;

    int fDimension;

public:
    //Default constructor
    GeometricMesh(){};
    
    GeometricMesh(GeometricMap geomap);

    //Default destructor
    ~GeometricMesh(){};

    void SetGeometricMap(GeometricMap &geomap);

    GeometricMap &GetGeometricMap() {
        return fGeoMap;
    }

    int &Dimension(){
        return fDimension;
    }

    // Number of nodes of the mesh
    int64_t NumberOfNodes() const;
    
    // Return the number of elements
    int64_t NumberOfElements() const;

    void SetNumberOfNodes(int64_t nnodes);
    void SetNumberOfElements(int64_t numelements);

    // Set computational element pointer
    void SetElement(int64_t elindex, GeometricElement *gel);

};

#endif