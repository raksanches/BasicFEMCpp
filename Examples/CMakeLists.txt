add_library(NewFEMlib ${GMSH_INTERFACE} ${INTEGRATION} ${MATERIAL} ${SHAPE_FUNCTION} ${TOPOLOGY} ${UTILITY} ${NOT_CLASSIFIED})
target_link_libraries(NewFEMlib PRIVATE Eigen3::Eigen)

# add_executable(BasicFEM Main.cpp)
# target_link_libraries (BasicFEM NewFEMlib Eigen3::Eigen metis ${MPI_LIBRARIES} ${PETSC_LIBRARIES})
