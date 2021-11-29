#ifndef TOPOLOGY_LINEAR
#define TOPOLOGY_LINEAR

#include "TopologyTypes.h"
#include "IntegrationRuleLinear.h"

/*
    Topology class associated to line elements
    The parametric space is a one dimensional line  between -1 and 1
 */
class TopologyLinear
{
public:
    
    // Type definition for linear integration rule
    typedef IntegrationRuleLinear LocalIntRule;
    
    // Number of sides associated to linear elements
    const static int nSides = 3;

    // Number of nodes associated to linear elements
    const static int nCorners = 2;
    
    // Dimension of linear elements
    const static int Dimension = 1;
    
    // Number of nodes associated with a side
    static int NSideNodes(int side);
    
    // Local node index of a node associated with a side
    static int SideNodeLocIndex(int side, int node);
    
    // Return the topology type
    static TopologyType Type();
};

#endif
