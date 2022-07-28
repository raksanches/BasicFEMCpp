
#include "TopologyQuad.h"
#include <iostream>

// Number of sides associated with 1D elements
const int TopologyQuad::nSides;

// Number of nodes associated with 1D elements
const int TopologyQuad::nCorners;

// Dimension of 1D elements
const int TopologyQuad::Dimension;

int TopologyQuad::NSideNodes(int side) {
    if(side < 0 || side > 8) PanicButton();
    static int nsidenodes[9] = {1, 1, 1, 1, 2, 2, 2, 2, 4};
    return nsidenodes[side];
}

int TopologyQuad::SideNodeLocIndex(int side, int node) {
    if (side < 4 && node == 0) return side;
    if (side >= 4 && side < 8 && node < 4) return node;
    if (side == 8 && node < 4) return node;
    std::cout << "TopologyQuad::SideNodeIndex inconsistent side or node " << side
            << ' ' << node << std::endl;
    PanicButton();
    return -1;
}

TopologyType TopologyQuad::Type() {
    return TQuadrilateral;
}
