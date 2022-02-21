# Here we will search for eigen. If eigen is not found, we will download it.
function(enable_petsc)
    #perhaps eigen was already downloaded when running cmake
    if(NOT PETSC_POPULATED)
        find_package(PETSc QUIET CONFIG)

        if(NOT PETSC_FOUND)
            # Couldn't load via target, so fall back to allowing module mode finding, which will pick up
            # tools/FindEigen3.cmake
            find_package(PETSc QUIET)
        endif()
        if(NOT PETSC_FOUND)
            set(PETSC_VERSION_STRING "3.3.9")
            include(FetchContent)
            FetchContent_Declare(
                petsc
                GIT_REPOSITORY https://gitlab.com/petsc/petsc
                GIT_TAG ${PETSC_VERSION_STRING})

            FetchContent_GetProperties(petsc)
            if(NOT petsc_POPULATED)
                message(STATUS "Downloading PETSc")
                FetchContent_Populate(petsc)
                set(DOWNLOADED_PETSC TRUE)
            endif()

            set(PETSC_INCLUDE_DIR ${petsc_SOURCE_DIR})
            set(PETSC_FOUND TRUE)
        endif()
    endif()
    if(PETSC_FOUND)
        # if eigen was downloaded, the target was not created
        if(NOT TARGET PETSc::PETSc)
            add_library(PETSc::PETSc IMPORTED INTERFACE)
            set_property(TARGET PETSc::PETSc PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                "${PETSC_INCLUDE_DIR}")
        endif()

        # Eigen 3.3.1+ cmake sets EIGEN3_VERSION_STRING (and hard codes the version when installed
        # rather than looking it up in the cmake script); older versions, and the
        # tools/FindEigen3.cmake, set EIGEN3_VERSION instead.
        if(NOT PETSC_VERSION AND PETSC_VERSION_STRING)
            set(PETSC_VERSION ${PETSC_VERSION_STRING})
        endif()
        message(STATUS "PETSc found at ${PETSC_INCLUDE_DIR}")
    else()
        message(FATAL_ERROR "Could not satisfy dependency: PETSc")
    endif()
endfunction()