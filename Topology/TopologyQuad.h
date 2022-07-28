#ifndef TOPOLOGY_QUAD
#define TOPOLOGY_QUAD

#include "TopologyTypes.h"
#include "IntegrationRuleLine.h"

/*
    Topology class associated to quad elements
    The parametric space is a two dimensional quad  between -1 and 1
 */
class TopologyQuad
{
public:
    
    // Type definition for quad integration rule
    typedef TopologyQuad LocalIntRule;
    
    // Number of sides associated to quad elements
    const static int nSides = 9;

    // Number of nodes associated to quad elements
    const static int nCorners = 4;
    
    // Dimension of quad elements
    const static int Dimension = 2;
    
    // Number of nodes associated with a side
    static int NSideNodes(int side);
    
    // Local node index of a node associated with a side
    static int SideNodeLocIndex(int side, int node);
    
    // Return the topology type
    static TopologyType Type();
};

#endif
