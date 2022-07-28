#include "GeometricElementT.h"
#include "GeometricLine.h"

template<class geom>
GeometricElementT<geom>::GeometricElementT(const VecInt &nodeindices, int matid, GeometricMesh* gmesh, int index){
    if(index >= gmesh->NumberOfElements()) gmesh->SetNumberOfElements(index + 1);
    if(nodeindices.size() != fGeom.nCorners) PanicButton();
    fGeom.SetNodes(nodeindices);
    
    gmesh->SetElement(index, this);
}


template class GeometricElementT<GeometricLine>;
// template class GeometricElementT<GeometricQuad>;