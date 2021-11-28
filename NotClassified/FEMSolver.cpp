#include "FEMSolver.h"

FEMSolver::FEMSolver(Geometry* geometry, const int &index)
{
	geometry_ = geometry;
	index_ = index;
}

FEMSolver::~FEMSolver() {}


//Functions of FEMSolver

std::vector<std::string> split(std::string str, std::string delim)
{
	std::istringstream is(str);
	std::vector<std::string> values;
	std::string token;
	while (getline(is, token, ' '))
		values.push_back(token);
	return values;
}

std::vector<int> intersection(std::vector<int> vector1, std::vector<int> vector2)
{
	std::sort(vector1.begin(), vector1.end());
	std::sort(vector2.begin(), vector2.end());

	std::vector<int> vector3;
	std::set_intersection(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(), std::back_inserter(vector3));

	return vector3;
}


Node* FEMSolver::getNode(const int& index)
{
	return nodes_[index];
}

Element* FEMSolver::getElement(const int& index)
{
	return elements_[index];
}

Material* FEMSolver::getMaterial(const int& index)
{
	return materials_[index];
}


std::vector<BoundaryCondition*> FEMSolver::getBoundaryConditions(const std::string& type)
{
	return boundaryConditions_[type];
}


void FEMSolver::addNode(const int& index, const bounded_vector<double,2>& initialCoordinate)
{
	Node* n = new Node(index, initialCoordinate);
	nodes_.push_back(n);
}

void FEMSolver::addElement(const int& index, const std::vector<int>& nodesIndex, const int& materialIndex, const double& thickness, const std::string& elementType)
{
	std::vector<Node*> nodes;
	nodes.reserve(nodesIndex.size());
	for (const int& i : nodesIndex)
		nodes.push_back(nodes_[i]);
	Element* e = new Element(index, nodes, materials_[materialIndex], thickness, elementType);
	elements_.push_back(e);
}

void FEMSolver::addSurfaceMaterial(const std::vector<PlaneSurface*> surfaces, const double& viscosity, const double& density)
{
	int index = materials_.size();
	Material* m = new Material(index, viscosity, density);
	materials_.push_back(m);
	for (PlaneSurface* surface : surfaces)
		surface->setMaterial(m);
}

void FEMSolver::readInput(const std::string& inputFile, const bool& deleteFiles)
{
	//defyning the maps that are used to store the elements information
	std::unordered_map<int, std::string> gmshElement = { {1, "line"}, {2, "triangle"}, {3, "quadrilateral"}, {8, "line3"}, {9, "triangle6"}, {10, "quadrilateral9"}, {15, "vertex"}, {16, "quadrilateral8"}, {20, "triangle9"}, {21, "triangle10"}, {26, "line4"}, {36, "quadrilateral16"}, {39, "quadrilateral12"} };
	std::unordered_map<std::string, int> numNodes = { {"vertex", 1}, {"line", 2}, {"triangle", 3}, {"quadrilateral", 4}, {"line3", 3}, {"triangle6", 6}, {"quadrilateral8", 8}, {"quadrilateral9", 9}, {"line4", 4}, {"triangle", 9}, {"triangle10", 10}, {"quadrilateral12", 12}, {"quadrilateral16", 16}};
	std::unordered_map<std::string, std::string> supportedElements = { {"triangle", "T3"}, {"triangle6", "T6"}, {"triangle10", "T10"}, {"quadrilateral", "Q4"}, {"quadrilateral8", "Q8"}, {"quadrilateral9", "Q9"}, {"quadrilateral12", "Q12"}, {"quadrilateral16", "Q16"} };
	std::unordered_map<Line*, std::vector< std::vector<int> >> lineElements;

	//opening the .msh file
	std::ifstream file(inputFile);
	std::string line;
	std::getline(file, line); std::getline(file, line); std::getline(file, line); std::getline(file, line);

	//reading physical entities
	int number_physical_entities;
	file >> number_physical_entities;
	std::getline(file, line);
	std::unordered_map<int, std::string> physicalEntities;
	physicalEntities.reserve(number_physical_entities);
	for (int i = 0; i < number_physical_entities; i++)
	{
		std::getline(file, line);
		std::vector<std::string> tokens = split(line, " ");
		int index;
		std::istringstream(tokens[1]) >> index;
		physicalEntities[index] = tokens[2].substr(1, tokens[2].size() - 2);
	}
	std::getline(file, line); std::getline(file, line);

	//reading nodes
	int number_nodes;
	file >> number_nodes;
	nodes_.reserve(number_nodes);
	std::getline(file, line);
	for (int i = 0; i < number_nodes; i++)
	{
		std::getline(file, line);
		std::vector<std::string> tokens = split(line, " ");
		bounded_vector<double,2> coord;
		std::istringstream(tokens[1]) >> coord(0);
		std::istringstream(tokens[2]) >> coord(1);
		addNode(i, coord);
	}
	std::getline(file, line); std::getline(file, line);

	//reading elements
	int number_elements;
	file >> number_elements;
	elements_.reserve(number_elements);
	std::getline(file, line);
	int cont = 0;
	for (int i = 0; i < number_elements; i++)
	{
		std::getline(file, line);
		std::vector<std::string> tokens = split(line, " ");
		std::vector<int> values(tokens.size(), 0);
		for (size_t j = 0; j < tokens.size(); j++)
			std::istringstream(tokens[j]) >> values[j];
		std::string elementType = gmshElement[values[1]];
		int number_nodes_per_element = numNodes[elementType];
		std::vector<int> elementNodes;
		elementNodes.reserve(number_nodes_per_element);
		for (size_t j = 5 ; j < values.size(); j++)
			elementNodes.push_back(values[j]-1);
		std::string name = physicalEntities[values[3]];
		//Adding 2D elements to surfaces
		if (name[0] == 's')
		{
			if (supportedElements.find(elementType) == supportedElements.end())
			{
				std::cout << elementType << " is not supported.\n";
				exit(EXIT_FAILURE);
			}
			PlaneSurface* object = geometry_->getPlaneSurface(name);
			int materialIndex = object->getMaterial()->getIndex();
			double thickness = object->getThickness();
			addElement(cont, elementNodes, materialIndex, thickness, supportedElements[elementType]);
			object->addElementToSurface(elements_[cont]);
			//Verifying if an element side touches a line
			for (auto it = lineElements.begin(); it != lineElements.end();)
			{
				auto& key = it->first;
				auto& value = it->second;
				int it2 = 0;
				for (auto it1 = value.begin(); it1 != value.end();)
				{
					auto nodes = lineElements[key][it2];
					std::sort(nodes.begin(), nodes.end());
					if (intersection(nodes, elementNodes) == nodes)
					{
						key->appendPlaneElement(elements_[cont]);
						it1 = value.erase(it1);
					}
					else
					{
						it1++;
						it2++;
					}
				}
				if (value.size() == 0)
					it = lineElements.erase(it);
				else
					it++;
			}
			cont += 1;
		}
		//Adding 1D elements to lines
		else if (name[0] == 'l')
		{
			Line* object = geometry_->getLine(name);
			std::vector<Node*> nodes;
			nodes.reserve(elementNodes.size());
			for (int index : elementNodes)
				nodes.push_back(nodes_[index]);
			object->appendNodes(nodes);
			if (lineElements.count(object) != 1)
				lineElements[object] = std::vector< std::vector<int> >();
			lineElements[object].push_back(elementNodes);
		}
		//Adding a node to point
		else
		{
			// Point* object = geometry_->getPoint(name);
			// object->addNodeToPoint(getNode(elementNodes[0]));
		}
	}
	//Closing the file
	file.close();
	if (deleteFiles)
		system((remove + inputFile).c_str());
}

std::vector<int> FEMSolver::getConstrains()
{
	std::vector<int> dof;
	//setting dof that are constrained
	for (BoundaryCondition* bc : boundaryConditions_["POINT_DISPLACEMENT"])
	{
		int nodeIndex = bc->getNodeIndex();

		int dofIndex = nodes_[nodeIndex] -> getDOFNode();
				nodes_[nodeIndex]->setConstrain(true);

		for (size_t i = 0; i < 2; i++)
		{
			if (bc->getComponent(i).size() != 0)
			{
				dof.push_back(2*dofIndex + i);
			}
		}
	

	}
	return dof;
}

std::vector<int> FEMSolver::getConstrains1()
{
	std::vector<int> dof;
	//setting dof that are constrained
	for (BoundaryCondition* bc : boundaryConditions_["POINT_DISPLACEMENT"])
	{
		int nodeIndex = bc->getNodeIndex();
		int dofIndex = nodeIndex;// nodes_[nodeIndex] -> getDOFNode();
		nodes_[nodeIndex]->setConstrain(true);

		for (size_t i = 0; i < 2; i++)
		{
			if (bc->getComponent(i).size() != 0)
			{
				dof.push_back(2*dofIndex + i);
			}
		}

	}
	return dof;
}


void FEMSolver::addBoundaryConditions()
{
	//transfering neumann conditions
	for (auto gbc : geometry_->getBoundaryConditions("NEUMANN"))
	{
		//transfering point loads applied to points
		if (gbc->getLineName().length() == 0)
		{
			std::string pointName = gbc->getPointName();
			std::string referenceSystem = gbc->getReferenceSystem();
			std::vector<double> componentX = gbc->getComponentX();
			std::vector<double> componentY = gbc->getComponentY();
			std::string method = gbc->getMethod();
			double penaltyParameter = gbc->getPenaltyParameter();
			std::string type = "POINT_LOAD";
			if (boundaryConditions_.count(type) == 0)
				boundaryConditions_[type] = std::vector<BoundaryCondition*>();
			int index = boundaryConditions_[type].size();
			Point* point = geometry_->getPoint(pointName);
			Node* node = point->getPointNode();
			BoundaryCondition* bc = new BoundaryCondition(index, node->getIndex(), componentX, componentY, method, referenceSystem, penaltyParameter);
			boundaryConditions_[type].push_back(bc);
		}
		//transfering distributed loads
		// else
		// {
		// 	std::string lineName = gbc->getLineName();
		// 	std::string referenceSystem = gbc->getReferenceSystem();
		// 	std::vector<double> componentX = gbc->getComponentX();
		// 	std::vector<double> componentY = gbc->getComponentY();
		// 	std::string method = gbc->getMethod();
		// 	double penaltyParameter = gbc->getPenaltyParameter();
		// 	std::string type = "DIST_LOAD";
		// 	if (boundaryConditions_.count(type) == 0)
		// 		boundaryConditions_[type] = std::vector<BoundaryCondition*>();
		// 	int index = boundaryConditions_[type].size();
		// 	Line* line = geometry_->getLine(lineName);
		// 	Node* node = point->getPointNode();
		// 	BoundaryCondition* bc = new BoundaryCondition(index, node->getIndex(), componentX, componentY, method, referenceSystem, penaltyParameter);
		// 	boundaryConditions_[type].push_back(bc);
		// }
	}

	for (auto gbc : geometry_->getBoundaryConditions("DIRICHLET"))
	{
		//transfering point displacements applied to points
		if (gbc->getLineName().length() == 0)
		{
			std::string pointName = gbc->getPointName();
			std::string referenceSystem = gbc->getReferenceSystem();
			std::vector<double> componentX = gbc->getComponentX();
			std::vector<double> componentY = gbc->getComponentY();
			std::string method = gbc->getMethod();
			double penaltyParameter = gbc->getPenaltyParameter();
			std::string type = "POINT_DISPLACEMENT";
			if (boundaryConditions_.count(type) == 0)
				boundaryConditions_[type] = std::vector<BoundaryCondition*>();
			int index = boundaryConditions_[type].size();
			Point* point = geometry_->getPoint(pointName);
			Node* node = point->getPointNode();
			BoundaryCondition* bc = new BoundaryCondition(index, node->getIndex(), componentX, componentY, method, referenceSystem, penaltyParameter);
			boundaryConditions_[type].push_back(bc);
		}
		//transfering point displacements applied to lines
		if (gbc->getPointName().length() == 0)
		{
			std::string lineName = gbc->getLineName();
			std::string referenceSystem = gbc->getReferenceSystem();
			std::vector<double> componentX = gbc->getComponentX();
			std::vector<double> componentY = gbc->getComponentY();
			std::string method = gbc->getMethod();
			double penaltyParameter = gbc->getPenaltyParameter();
			std::string type = "POINT_DISPLACEMENT";
			if (boundaryConditions_.count(type) == 0)
				boundaryConditions_[type] = std::vector<BoundaryCondition*>();
			int index = boundaryConditions_[type].size();
			Line* line = geometry_->getLine(lineName);
			for (Node* node : line->getLineNodes())
			{
				BoundaryCondition* bc = new BoundaryCondition(index, node->getIndex(), componentX, componentY, method, referenceSystem, penaltyParameter);
				boundaryConditions_[type].push_back(bc);
				index++;
			}
		}
		//transfering line displacements applied to lines

	}
	
}

void FEMSolver::generateMesh(const std::string& elementType, const std::string& algorithm, std::string geofile, const std::string& gmshPath, const bool& plotMesh, const bool& showInfo)
{	

    	int rank, size;
    MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
    MPI_Comm_size(PETSC_COMM_WORLD, &size);

    
    	std::pair<std::string, bool> pair; pair.second = false;
  	if (rank == 0)
  	{
		pair = createMesh(geometry_, elementType, algorithm, geofile, gmshPath, plotMesh, showInfo);

    
		for (int i = 1; i < size; i++)
		{
			MPI_Send(pair.first.c_str(), pair.first.length()+1, MPI_CHAR, i, 0, PETSC_COMM_WORLD);
			if (i == size-1)
			{
				MPI_Send(&pair.second, 1, MPI_C_BOOL, i, 1, PETSC_COMM_WORLD);
				pair.second = false;
			}
		}
	}
	else
	{
		MPI_Status status;
		MPI_Probe(0, 0, PETSC_COMM_WORLD, &status);
		int count;
		MPI_Get_count(&status, MPI_CHAR, &count);
		char buf[count+1];
		MPI_Recv(&buf, count+1, MPI_CHAR, 0, 0, PETSC_COMM_WORLD, &status);
		pair.first = buf;
		if (rank == size-1)
			MPI_Recv(&pair.second, 1, MPI_C_BOOL, 0, 1, PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	readInput(pair.first, pair.second);

	addBoundaryConditions();

 	 domainDecompositionMETIS();
}

void FEMSolver::solveLinearElasticity(){
    std::cout<<"to be implemented"<<std::endl;   
}

void FEMSolver::exportToParaview(const int& timestep)
{
	std::stringstream text;
	text << "results/" << "Output" << timestep << ".vtu";
	std::ofstream file(text.str());
	file.precision(16);

	//header
	file << "<?xml version=\"1.0\"?>" << "\n"
         << "<VTKFile type=\"UnstructuredGrid\">" << "\n"
		 << "  <UnstructuredGrid>" << "\n"
         << "  <Piece NumberOfPoints=\"" << nodes_.size()
         << "\"  NumberOfCells=\"" << elements_.size()
         << "\">" << "\n";
	//nodal coordinates
	file << "    <Points>" << "\n"
         << "      <DataArray type=\"Float64\" "
         << "NumberOfComponents=\"3\" format=\"ascii\">" << "\n";
    for (Node* n : nodes_)
	{
		file << n->getCurrentCoordinate()(0) << " " << n->getCurrentCoordinate()(1) << " " << 0.0 << "\n";
	}
    file << "      </DataArray>" << "\n"
         << "    </Points>" << "\n";
	//element connectivity
	file << "    <Cells>" << "\n"
         << "      <DataArray type=\"Int32\" "
         << "Name=\"connectivity\" format=\"ascii\">" << "\n";
    for (Element* e : elements_)
	{
		for (Node* n : e->getNodes())
		{
			file << n->getIndex() << " ";
		}
		file << "\n";
	}

	file << "      </DataArray>" << "\n";
	//offsets
	file << "      <DataArray type=\"Int32\""
		 << " Name=\"offsets\" format=\"ascii\">" << "\n";
	int aux = 0;
	for (Element* e : elements_)
	{
		aux += 3;
		file << aux << "\n";
	}
	file << "      </DataArray>" << "\n";
	//elements type
	file << "      <DataArray type=\"UInt8\" Name=\"types\" "
		 << "format=\"ascii\">" << "\n";

	for (Element* e : elements_)
	{
		file << 5 << "\n";
	}
	file << "      </DataArray>" << "\n"
		 << "    </Cells>" << "\n";
	//nodal results
	file << "    <PointData>" <<"\n";
	file << "      <DataArray type=\"Float64\" NumberOfComponents=\"3\" "
		<< "Name=\"Displacement\" format=\"ascii\">" << "\n";

	for (Node* n: nodes_)
	{
		double dx=0;
		double dy=0;
		// std::cout << dx << " "
		// 	 << dy  << std::endl;
		file << dx << " "
			 << dy  << " " << 0.0 << "\n";
	}
	file << "      </DataArray> " << "\n";
	file << "    </PointData>" << "\n";
	//elemental results
	file << "    <CellData>" << "\n";

	file << "    </CellData>" << "\n";
	//footnote
	file << "  </Piece>" << "\n"
		<< "  </UnstructuredGrid>" << "\n"
		<< "</VTKFile>" << "\n";
	file.close();

}

void FEMSolver::domainDecompositionMETIS() {
    
    std::string mirror2;
    mirror2 = "domain_decomposition.txt";
    std::ofstream mirrorData(mirror2.c_str());
    
    int size;

    MPI_Comm_size(PETSC_COMM_WORLD, &size);

    idx_t objval;
    idx_t numEl = elements_.size();
    idx_t numNd = nodes_.size();
    idx_t ssize = size;
    idx_t one = 1;
    idx_t elem_start[numEl+1], elem_connec[3*numEl];
    elementPartition_ = new idx_t[numEl];
    nodePartition_ = new idx_t[numNd];


    for (idx_t i = 0; i < numEl+1; i++)
	{
        elem_start[i]=3*i;
    }
    for (idx_t jel = 0; jel < numEl; jel++)
	{
        
        
        for (idx_t i=0; i < elements_[jel]->getNodes().size(); i++)
		{	
			int nodeIndex = elements_[jel]->getNodes()[i]->getIndex();
        	elem_connec[3*jel+i] = nodeIndex;
        }
    }

    //Performs the domain decomposition
	if (size == 1)
	{
		for (Node *node : nodes_)
			nodePartition_[node->getIndex()] = 0;
		for (Element *el : elements_)
			elementPartition_[el->getIndex()] = 0;
	}
	else
	{
		METIS_PartMeshDual(&numEl, &numNd, elem_start, elem_connec,
						NULL, NULL, &one, &ssize, NULL, NULL,
						&objval, elementPartition_, nodePartition_);
	}

    mirrorData << std::endl \
               << "MESH DOMAIN DECOMPOSITION - ELEMENTS" << std::endl;
    for (int i = 0; i < elements_.size(); i++)
	{
        mirrorData << "process = " << elementPartition_[i] \
                   << ", element = " << i << std::endl;
    }

    mirrorData << std::endl \
               << "MESH DOMAIN DECOMPOSITION - NODES" << std::endl;
    for (int i = 0; i < nodes_.size(); i++)
	{
        mirrorData << "process = " << nodePartition_[i] \
                   << ", node = " << i << std::endl;
    }

}
