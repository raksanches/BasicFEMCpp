//generating Mesh
Geometry* Solid2D = new Geometry(0);

//Create base points
Point* p1 = Solid2D->addPoint({ 0., 0. }, 0.1);
Point* p2 = Solid2D->addPoint({ 1., 0. }, 0.1);
Point* p3 = Solid2D->addPoint({ 1., 1. }, 0.1);
Point* p4 = Solid2D->addPoint({ 0., 1. }, 0.1);

//Create base lines;
Line* l1 = Solid2D->addLine({ p1, p2});
Line* l2 = Solid2D->addLine({ p2, p3});
Line* l3 = Solid2D->addLine({ p3, p4});
Line* l4 = Solid2D->addLine({ p4, p1});

//Create surfaces. parameter: vector of lines
PlaneSurface* s1 = Solid2D->addPlaneSurface({ l1, l2, l3, l4});

//setting number of line division for mesh creation: line, ndiv
Solid2D->transfiniteLine({ l1 }, 10);
Solid2D->transfiniteLine({ l2 }, 10); 
Solid2D->transfiniteLine({ l3 }, 10);
Solid2D->transfiniteLine({ l4 }, 10);

//adding boundary conditions
Solid2D->addBoundaryCondition("DIRICHLET", l1, {0.0}, {0.0}, "GLOBAL");
Solid2D->addBoundaryCondition("DIRICHLET", l3, {0.0}, {0.0}, "GLOBAL");
Solid2D->addBoundaryCondition("DIRICHLET", l4, {1.0}, {0.0}, "GLOBAL");

//creating Solid2D solver. parameter: Geometry 
FEMSolver* problem = new FEMSolver(Solid2D);

//adding material properties.
// parameters: surface, Young's Modulus, Poisson Ratio
problem->addSurfaceMaterial({ s1 }, 200.0e9, 0.3);

// generating mesh. parameters: element type, method, file .geo name, gmsh path, show mesh, mesh information

problem->generateMesh("T3", "FRONT", "Solid2D", "../GmshInterface", false, false);


