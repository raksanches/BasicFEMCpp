MANSEC           = KSP
CLEANFILES       = rhs.vtk solution.vtk
NP               = 1
CSOURCES 		 = $(wildcard *.cpp src/*.cpp  src/mesh_interface/*.cpp)
FCOMPILER        = gfortran -O2
CXXFLAGS        += -w -DANSI_DECLARATORS

include ${PETSC_DIR}/lib/petsc/conf/variables
include ${PETSC_DIR}/lib/petsc/conf/rules
include ${PETSC_DIR}/lib/petsc/conf/test

solve: $(CSOURCES:.cpp=.o) 
	@-${CLINKER} -o $@ $^ ${PETSC_KSP_LIB} -lboost_system -std=c++11

debug: $(CSOURCES:.cpp=.o)
	@-${CLINKER} -o $@ $^ ${PETSC_KSP_LIB} -g
	@gdb debug

clearall:
	@$ rm *.o src/*.o  *solve results/*.vtu

clearinput:
	@$ rm Main.o results/*.vtu *solve

run1:
	./f

run2:
	@$ mpirun -np 2 ./solve

run4:
	@$ mpirun -np 4 ./solve

run8:
	@$ mpirun -np 8 ./solve


