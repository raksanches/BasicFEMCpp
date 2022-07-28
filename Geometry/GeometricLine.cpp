#include "GeometricLine.h"



void GeometricLine::SetNodes(const VecInt &nodes) {
    if(nodes.rows() != 2) PanicButton();
    fNodeIndices = nodes;
}