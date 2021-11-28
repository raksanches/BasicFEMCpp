static char help[] = "Basic FEM code";


#include "FEMSolver.h"
#include "PanicButton.h"

int main(int argc, char **args)
{
	// Starts main program invoking PETSc
    PetscInitialize(&argc, &args, (char*)0, help);

    int rank, size;

    MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
    MPI_Comm_size(PETSC_COMM_WORLD, &size);

    //creatin mesh, setting materials and boundary conditions
	#include "test.h"

    //solving  problem:
	problem->solveLinearElasticity();
    
    //Example of a Panic Button
    // PanicButton();
    //printing solution
    problem->exportToParaview(1);
  
	PetscFinalize();

	return 0;
}
