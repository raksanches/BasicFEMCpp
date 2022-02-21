#include "catch2/catch.hpp"
#include <mpi.h>
#include <iostream>

TEST_CASE("reduce")
{
    std::cout << "Hello World" << std::endl;
    // int size;
    // MPI_Comm_size(MPI_COMM_WORLD, &size);
    // int rank;
    // MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // rank++;
    // // aritmetic series
    // int sum;
    // MPI_Allreduce(&rank, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // REQUIRE(sum == (size*(1 + size))/2 );
}

