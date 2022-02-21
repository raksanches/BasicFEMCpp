#pragma once

#include "Geometry.h"
#include "Mesh.h"
#include "BoundaryCondition.h"
//#include "triangle.h"


#include <unordered_map>
#include <petscksp.h>
#include <metis.h>
#include "eigen3/Eigen/Dense"
using namespace Eigen;

//#include <fstream.h>

class FEMSolver
{
public:

    //Create FE domain geometry
	FEMSolver(Geometry* geometry, const int &index= 0);


	~FEMSolver();


    //Functions of FEMSolver

	Node* getNode(const int& index);

	Element* getElement(const int& index);

	Material* getMaterial(const int& index);

	std::vector<BoundaryCondition*> getBoundaryConditions(const std::string& type);

	void setAnalysisParameters(const int& numberOfTimeSteps, const double& deltat, const double& gravity, const double& rhoInf);

	void addNode(const int& index, const Vector2d& initialCoordinate);

	void addSurfaceMaterial(const std::vector<PlaneSurface*> surfaces, const double& viscosity, const double& density);

	void addElement(const int& index, const std::vector<int>& nodes, const int& materialIndex, const double& thickness, const std::string& elementType);

	void generateMesh(const std::string& elementType = "T3", const std::string& algorithm = "AUTO", std::string geofile = std::string(), const std::string& gmshPath = std::string(), const bool& plotMesh = true, const bool& showInfo = false);

	void readInput(const std::string& inputFile, const bool& deleteFiles = true);

	std::vector<int> getConstrains();

	std::vector<int> getConstrains1();

	void addBoundaryConditions();

	void solveLinearElasticity();

	void exportToParaview(const int& timestep);


	void domainDecompositionMETIS();
  
	// variables
  int index_;
	Geometry * geometry_;
	std::vector<Node*> nodes_;
	std::vector<Element*> elements_;
	std::vector<Material*> materials_;
	std::unordered_map<std::string, std::vector<BoundaryCondition*> > boundaryConditions_;
	idx_t* elementPartition_;
	idx_t* nodePartition_;
	double area_;

	bool analysisType_;
};
