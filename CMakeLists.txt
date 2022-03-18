#===================================================================================================== PROJECT SETUP ===
cmake_minimum_required(VERSION 3.14)
project(abaqus_tools VERSION 0.1.0)

# Set common project paths relative to project root directory
set(CPP_SRC_PATH "src/cpp")
set(CMAKE_SRC_PATH "src/cmake")

# Add the cmake folder to locate project CMake module(s)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/${CMAKE_SRC_PATH}" ${CMAKE_MODULE_PATH})

# Get version number from Git
set(VERSION_UPDATE_FROM_GIT True)
# FIXME: Figure out why include() doesn't pick up CMAKE_MODULE_PATH correctly
include(${CMAKE_SRC_PATH}/GetVersionFromGitTag.cmake)
project(${PROJECT_NAME} VERSION ${${PROJECT_NAME}_VERSION})

# Add installation directory variables
include(GNUInstallDirs)

# Set the c++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lrt")

# Enable CTest
enable_testing()

#================================================================================================= FIND DEPENDENCIES ===
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
        # FIXME: The following two lines, 'string' and 'include_directories' commands, are HACKS required to get the
        # correct included directories for the abaqus_tools builds. For some reason, the abaqus_tools project doesn't
        # add the correct include libraries, despite finding the upstream packages. Suspect a header only project
        # gotcha. These commands can be removed if you can coax CMake to add the "-isystem
        # /projects/python/beta/include" arguments to the compiler command when building the tests.
        string(REPLACE "share/${package}/cmake" "" package_include ${${package}_DIR})
        include_directories(${package_include}/include)
    else()
        # Find related, but external, projects using FetchContent and building locally
        message(WARNING "Did not find an installed ${package} package. Attempting local build with FetchContent.")
        # TODO: Decide how to handle master/dev build differences. bash env variables for GIT TAG?
        FetchContent_Declare(
            ${package}
            GIT_REPOSITORY ssh://git@re-git.lanl.gov:10022/aea/material-models/${package}.git
            GIT_TAG        origin/dev
        )
        FetchContent_MakeAvailable(${package})
    endif()
endforeach(package)

#=============================================================================================== ADD PROJECT TARGETS ===
# MUST COME AFTER DEPENDENCY LOCATING
# Add project source directories
include_directories("${CPP_SRC_PATH}")
add_subdirectory("${CPP_SRC_PATH}")

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

# CMake won't build the targets for local builds of upstream projects
if(cmake_build_type_lower STREQUAL release)
    install(EXPORT ${PROJECT_NAME}_Targets
            FILE ${PROJECT_NAME}Targets.cmake
            DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
endif()

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
