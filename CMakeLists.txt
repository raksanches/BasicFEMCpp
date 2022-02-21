cmake_minimum_required (VERSION 3.14)

project(BasicFEM)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")

find_package(MPI)
find_package(PETSc)

# Eigen
include(CMakeModules/EnableEigen.cmake)
enable_eigen()

# Catch2
include(CMakeModules/EnableCatch2.cmake)
enable_catch2()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#[[
If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their definition
and dump it in the cache along with proper documentation, otherwise set CMAKE_BUILD_TYPE
to Debug prior to calling PROJECT(). This assumes you're only build one type of solution
a time. If you're working with multiple solutions like Visual Studio Professional can do,
you need to comment this out.
]]
if(DEFINED CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the type of build, options are: Debug, Release.")
else() # CMAKE_BUILD_TYPE
   set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug, Release.")
endif() # CMAKE_BUILD_TYPE

set(CMAKE_CXX_STANDARD 17)

include_directories(include ${MPI_INCLUDE_PATH} ${PETSC_INCLUDES})
add_definitions(${PETSC_DEFINITIONS})

link_directories(${PETSC_DIR}/${PETSC_ARCH}/lib)

# PROJECT FILES
add_subdirectory(GmshInterface)
add_subdirectory(Integration)
# add_subdirectory(Libs)
add_subdirectory(Material)
add_subdirectory(NotClassified)
add_subdirectory(ShapeFunction)
add_subdirectory(Topology)
add_subdirectory(Utility)

#Specify where the headers files must be found
include_directories(
	"${PROJECT_SOURCE_DIR}/GmshInterface"
	"${PROJECT_SOURCE_DIR}/Integration"
    # "${PROJECT_SOURCE_DIR}/Libs"
    "${PROJECT_SOURCE_DIR}/Material"
    "${PROJECT_SOURCE_DIR}/NotClassified"
    "${PROJECT_SOURCE_DIR}/ShapeFunction"
    "${PROJECT_SOURCE_DIR}/Topology"
    "${PROJECT_SOURCE_DIR}/Utility"
)


#To enable unit test using Catch2 UnitTest framework
option(BUILD_UNITTEST "Whether the Catch2 UnitTest will be linked in" OFF)
if(BUILD_UNITTEST)
  include(CMakeModules/add_unit_test.cmake)
  include(CMakeModules/EnableCatch2.cmake)
  enable_catch2()
endif()

## inserting main definitions
#specifying the path to FemSC source code
#set(FemSCSOURCE ${FemSC_SRCS} ${FemSC_tinyxml} ${FemSC_HEAD})

set(BasicFEM ${BASIC_TYPES} ${GMSH_INTERFACE} ${NOT_CLASSIFIED} ${UTILITY} ${TOPOLOGY} ${SHAPE_FUNCTION} ${MATERIAL} ${INTEGRATION})

add_subdirectory(Examples)


if(BUILD_UNITTEST)
    add_subdirectory(UnitTest)
    #Enabling tests
    ENABLE_TESTING()
    include(CTest)
endif()