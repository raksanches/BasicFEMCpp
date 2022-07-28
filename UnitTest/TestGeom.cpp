
#include <iostream>
#include <math.h>

#include "DenseEigen.h"
#include "GeometricNode.h"
#include "GeometricLine.h"
#include "GeometricElementT.h"
#include "GeometricElement.h"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
using namespace Catch::literals;

using std::cout;
using std::endl;
using std::cin;

void CreateNode()
{
    //Test default constructor
    GeometricNode *node1 = new GeometricNode(); 
    REQUIRE(node1);

    //Test real constructor
    VecDouble coord(3);
    coord[0] = 1.;
    coord[1] = 2.;
    coord[2] = 3.;
    int64_t index = 1000;

    GeometricNode *node2 = new GeometricNode(coord,index);
    VecDouble n2coord = node2->GetCoordinates();
    bool vCoord = false;
    if (n2coord == coord) vCoord = true;
    
    REQUIRE(node2);
    REQUIRE(vCoord);
}

template<class T>
void CreateElement(){

    //Test default constructor
    GeometricElementT<T> *el1 = new GeometricElementT<T>(); 
    REQUIRE(el1);

    //Test real constructor
    GeometricMesh * gmesh = new GeometricMesh();
    int iEl = 0;
    int matid = 1;
    VecInt nodes(2);
    nodes[0] = iEl;
    nodes[1] = iEl + 1;
    GeometricElement *gel = new GeometricElementT<T>(nodes, matid, gmesh, iEl);
    gmesh->SetElement(iEl, gel);
    REQUIRE(gel);

}

TEST_CASE("Geom_Test")
{
    
    SECTION("Node Creation")
    {
        CreateNode();   
    }

    SECTION("Element Creation")
    {
        CreateElement<GeometricLine>();   
    }
    
}
