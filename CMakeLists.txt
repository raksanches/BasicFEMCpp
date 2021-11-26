project(BasicFEM)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

find_package(MPI)
find_package(PETSc REQUIRED)

include_directories(include ${MPI_INCLUDE_PATH} ${PETSC_INCLUDES})
add_definitions(${PETSC_DEFINITIONS})

add_subdirectory(src)

link_directories(${PETSC_DIR}/${PETSC_ARCH}/lib)

add_executable(${PROJECT_NAME} Main.cpp ${CXX_SOURCE_FILES} ${GMSH_SOURCE_FILES})

target_link_libraries(BasicFEM metis ${MPI_LIBRARIES} ${PETSC_LIBRARIES})