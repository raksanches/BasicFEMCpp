# Here we will search for eigen. If eigen is not found, we will download it.
function(enable_mpi)
    #perhaps eigen was already downloaded when running cmake
    if(NOT MPI_POPULATED)
        find_package(MPI QUIET CONFIG)

        if(NOT MPI_FOUND)
            # Couldn't load via target, so fall back to allowing module mode finding, which will pick up
            # tools/FindEigen3.cmake
            find_package(MPI QUIET)
        endif()
        if(NOT MPI_FOUND)
            message(STATUS "Could not satisfy dependency: MPI")
        endif()
    endif()
    if(MPI_FOUND)
        # if eigen was downloaded, the target was not created
        if(NOT TARGET MPI::MPI)
            add_library(MPI::MPI IMPORTED INTERFACE)
            set_property(TARGET MPI::MPI PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                "${MPI_INCLUDE_DIR}")
        endif()

        # Eigen 3.3.1+ cmake sets EIGEN3_VERSION_STRING (and hard codes the version when installed
        # rather than looking it up in the cmake script); older versions, and the
        # tools/FindEigen3.cmake, set EIGEN3_VERSION instead.
        if(NOT MPI_VERSION AND MPI_VERSION_STRING)
            set(MPI_VERSION ${MPI_VERSION_STRING})
        endif()
        message(STATUS "MPI found at ${MPI_INCLUDE_DIR}")
    else()
        message(STATUS "Could not satisfy dependency: MPI")
    endif()
endfunction()