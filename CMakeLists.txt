#===================================================================================================== PROJECT SETUP ===
cmake_minimum_required (VERSION 3.14)
project (abaqus_tools VERSION 0.0.3)
enable_testing()

# Set common project paths relative to project root directory
set(CPP_SRC_PATH "src/cpp")
set(CMAKE_SRC_PATH "src/cmake")

# Set the c++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include project source code directory for use by all libraries and executables in this project
include_directories(${CPP_SRC_PATH})

#================================================================================================= FIND DEPENDENCIES ===
# Add the cmake folder to locate the FindSphinx module
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/${CMAKE_SRC_PATH}" ${CMAKE_MODULE_PATH})

# Set build type checks
string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_lower)
set(upstream_required "")
if(cmake_build_type_lower STREQUAL "release")
    set(upstream_required "REQUIRED")
endif()

# Find related, but external, projects in installed environment
include(FetchContent)
set(upstream_packages "vector_tools")
foreach(package ${upstream_packages})
    find_package(${package} ${upstream_required} CONFIG)
    if(${package}_FOUND)
        message(STATUS "Found ${package}: ${${package}_DIR}")
    else()
    # Find related, but external, projects using FetchContent and building locally
    message(WARNING "Did not find an installed ${package} package. Attempting local build with FetchContent.")
    # TODO: Decide how to handle master/dev build differences. bash env variables for GIT TAG?
    FetchContent_Declare(
        ${package}
        GIT_REPOSITORY ssh://git@xcp-stash.lanl.gov:7999/mm/${package}.git
        GIT_TAG        origin/dev
    )
    FetchContent_MakeAvailable(${package})
    endif()
endforeach(package)

#=============================================================================================== ADD PROJECT TARGETS ===
# MUST COME AFTER DEPENDENCY LOCATING
# Add project source directories
include_directories("${CPP_SRC_PATH}")
add_subdirectory(${CPP_SRC_PATH})

# Only add tests and documentation for current project builds. Protects downstream project builds.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Find Boost. Required for tests
    find_package(Boost 1.53.0 REQUIRED COMPONENTS unit_test_framework)
    # Add tests and docs
    add_subdirectory ("${CPP_SRC_PATH}/tests")
    add_subdirectory ("docs")
endif()

#==================================================================================== SETUP INSTALLATION CMAKE FILES ===
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)
configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/${CMAKE_SRC_PATH}/Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
