#===================================================================================================== PROJECT SETUP ===
cmake_minimum_required (VERSION 3.14)
project (abaqus_tools VERSION 0.0.2)
enable_testing()

# Set common project paths relative to project root directory
set(CPP_SRC_PATH "src/cpp")

# Configure version
configure_file("${CPP_SRC_PATH}/config.h.in" "${PROJECT_BINARY_DIR}/config.h")

# Set the c++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -ansi -pedantic -O3 -fmax-errors=5 -ggdb")

# Include project source code directory for use by all libraries and executables in this project
include_directories(${CPP_SRC_PATH})

#================================================================================================= FIND DEPENDENCIES ===
# Find eigen
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{HOME}/.local $ENV{HOME}/local/ $ENV{HOME})
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIR})

# Add the cmake folder to locate the FindSphinx module
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Find related, but external, projects
# TODO: Decide how to handle master/dev build differences. bash env variables for GIT TAG?
include(FetchContent)
FetchContent_Declare(
    vector_tools
    GIT_REPOSITORY ssh://git@xcp-stash.lanl.gov:7999/mm/vector_tools.git
    GIT_TAG        origin/dev
)
FetchContent_MakeAvailable(vector_tools)

#=============================================================================================== ADD PROJECT TARGETS ===
# MUST COME AFTER DEPENDENCY LOCATING
# Add project source directories
add_subdirectory ("${CPP_SRC_PATH}")

# Only add tests and documentation for current project builds. Protects downstream project builds.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Find Boost. Required for tests
    find_package(Boost 1.53.0 REQUIRED COMPONENTS unit_test_framework)
    # Add tests and docs
    add_subdirectory ("${CPP_SRC_PATH}/tests")
    add_subdirectory ("docs")
endif()
