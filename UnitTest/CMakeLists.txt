enable_testing()

add_library(test_library STATIC test_main.cpp)

if (APPLE)
  target_compile_definitions(test_library PUBLIC MACOSX)
endif()

target_link_libraries(test_library PUBLIC NewFEMlib Catch2::Catch2 Eigen3::Eigen HDF5::HDF5)

add_unit_test(TestShapeFunction TestShapeFunction.cpp)

if (ENABLE_MPI_PETSC)
    add_subdirectory(MPI)
endif()
