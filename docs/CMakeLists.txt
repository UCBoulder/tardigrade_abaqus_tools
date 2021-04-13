find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED)

# Find all the public headers
set(PROJECT_PUBLIC_HEADER_DIR ${PROJECT_SOURCE_DIR}/${CPP_SRC_PATH})
file(GLOB_RECURSE PROJECT_PUBLIC_HEADERS ${PROJECT_PUBLIC_HEADER_DIR}/*.h)

# Set doxygen variables
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/${CPP_SRC_PATH})
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Create doxygen output and command
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${PROJECT_PUBLIC_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                   COMMENT "Generating ${PROJECT_NAME} docs"
                   VERBATIM)

# Add doxygen target
add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

# Set sphinx variables
set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

# Explicit list of documentation source files because globbing won't trigger CMake config on re-builds
set(DOCUMENTATION_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/api.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/changelog.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/bitbucket_setup.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/build.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/contribution.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/devops.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/jenkins_pr_builder.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/jenkins_version_control.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/md2rst.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/project_brief.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/release_philosophy.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/stub.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/targets.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/theory.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/user.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/zreferences.rst
)

# Add sphinx command
add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
                   COMMAND
                       ${SPHINX_EXECUTABLE} -b html
                       # Tell Breathe where to find the Doxygen output
                       -Dbreathe_projects.${PROJECT_NAME}=${DOXYGEN_OUTPUT_DIR}/xml
                       ${SPHINX_SOURCE} ${SPHINX_BUILD}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS
                       # Other docs files you want to track should go here (or in some variable)
                       ${DOCUMENTATION_SOURCE}
                       ${DOXYGEN_INDEX_FILE}
                   MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
                   COMMENT "Generating ${PROJECT_NAME} documentation with Sphinx")

# Add sphinx target
add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})
