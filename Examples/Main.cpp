static char help[] = "Basic FEM code";


#include "FEMSolver.h"
#include "PanicButton.h"
#include "IntegrationRuleLinear.h"

int main(int argc, char **args)
{
	// Starts main program invoking PETSc
    PetscInitialize(&argc, &args, (char*)0, help);

    int rank, size;

    MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
    MPI_Comm_size(PETSC_COMM_WORLD, &size);

    //creatin mesh, setting materials and boundary conditions
	#include "test.h"

    IntegrationRuleLinear integ;
    integ.SetOrder(4);

    std::cout << integ.NPoints() << std::endl;
    for (int i = 0; i < integ.NPoints(); i++)
    {
        MatrixXd coord (1,1);
        double weig = 0.;
        integ.Point(i,coord,weig);
        std::cout << "Point " << i << "; Coord = " << coord << " , Weight = " << weig << std::endl; 
    }
    

    //solving  problem:
	problem->solveLinearElasticity();
    
    //Example of a Panic Button
    // PanicButton();
    //printing solution
    problem->exportToParaview(1);
  
	PetscFinalize();

	return 0;
}
