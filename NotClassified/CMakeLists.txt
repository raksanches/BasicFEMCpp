file(GLOB not_classified 
    BoundaryCondition.h
    Element.h
    Material.h
    Node.h

    BoundaryCondition.cpp
    Element.cpp
    Material.cpp
    Node.cpp)

set(NOT_CLASSIFIED ${not_classified} PARENT_SCOPE)

#Need to improve this part of CMake to only include the FEMSolver file when the ENABLE MPI_PETSC_FLAG is active
if (ENABLE_MPI_PETSC)
    file (GLOB not_classified
          *.h  *.cpp)
    set (NOT_CLASSIFIED ${not_classified} PARENT_SCOPE)
endif()