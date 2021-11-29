
#include "TopologyLinear.h"
#include <iostream>

// Number of sides associated with 1D elements
const int TopologyLinear::nSides;

// Number of nodes associated with 1D elements
const int TopologyLinear::nCorners;

// Dimension of 1D elements
const int TopologyLinear::Dimension;

int TopologyLinear::NSideNodes(int side) {
    if(side < 0 || side > 2) PanicButton();
    static int nsidenodes[3] = {1, 1, 2};
    return nsidenodes[side];
}

int TopologyLinear::SideNodeLocIndex(int side, int node) {
    if (side < 2 && node == 0) return side;
    if (side == 2 && node < 2) return node;
    std::cout << "TopologyLinear::SideNodeIndex inconsistent side or node " << side
            << ' ' << node << std::endl;
    PanicButton();
    return -1;
}

TopologyType TopologyLinear::Type() {
    return TLine;
}
