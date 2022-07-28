#include "GeometricMesh.h"



void GeometricMesh::SetGeometricMap(GeometricMap &geomap){
    fGeoMap = geomap;
};


void GeometricMesh::SetNumberOfNodes(int64_t nnodes) {
    fNodes.resize(nnodes);
}

void GeometricMesh::SetNumberOfElements(int64_t numelements) {
    fElements.resize(numelements);
}

int64_t GeometricMesh::NumberOfNodes() const {
    return fNodes.size();
}

int64_t GeometricMesh::NumberOfElements() const {
    return fElements.size();
}

void GeometricMesh::SetElement(int64_t elindex, GeometricElement *gel) {
    if(elindex >= fElements.size()) PanicButton();
    fElements[elindex] = gel;
}