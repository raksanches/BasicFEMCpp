enable_testing()

add_library(test_libraryMPI STATIC test_mainMPI.cpp)

if (APPLE)
  target_compile_definitions(test_libraryMPI PUBLIC MACOSX)
endif()

target_link_libraries(test_libraryMPI PUBLIC NewFEMlib Catch2::Catch2 Eigen3::Eigen)

add_unit_test(TestMPI TestMPI.cpp)
