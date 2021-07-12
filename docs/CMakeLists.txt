find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED)

# Find all the public headers
set(PROJECT_PUBLIC_HEADER_DIR ${PROJECT_SOURCE_DIR}/${CPP_SRC_PATH})
file(GLOB_RECURSE PROJECT_PUBLIC_HEADERS ${PROJECT_PUBLIC_HEADER_DIR}/*.h)
file(GLOB_RECURSE PROJECT_SOURCE_FILES ${PROJECT_PUBLIC_HEADER_DIR}/*.cpp)

#=================================================================== DOXYGEN ===
# Set doxygen variables
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/${CPP_SRC_PATH})
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen/Doxyfile)

# Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Create doxygen output and command
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS
                       ${PROJECT_PUBLIC_HEADERS}
                       ${PROJECT_SOURCE_FILES}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                   COMMENT "Generating ${PROJECT_NAME} Doxygen API"
                   VERBATIM)

# Add doxygen target
add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

#=================================================================== SPHINX ===
# Set sphinx variables
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)
set(SPHINX_IN ${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in)
set(SPHINX_OUT ${CMAKE_CURRENT_BINARY_DIR}/sphinx/conf.py)

# Replace variables inside @@ with the current values
configure_file(${SPHINX_IN} ${SPHINX_OUT} @ONLY)

# Explicit list of documentation source files because globbing won't trigger CMake config on re-builds
set(DOCUMENTATION_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/api.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/changelog.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/build.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/contribution.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/devops.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/project_brief.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/release_philosophy.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/targets.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/theory.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/user.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/zreferences.rst
    ${CMAKE_CURRENT_SOURCE_DIR}/software.bib
)

# Add sphinx command
add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
                   COMMAND
                       ${CMAKE_COMMAND} -E copy
                           ${CMAKE_CURRENT_SOURCE_DIRECTORY}/${DOCUMENTATION_SOURCE}
                           ${SPHINX_BUILD}
                   COMMAND
                       ${SPHINX_EXECUTABLE} -M html
                       ${SPHINX_BUILD} ${SPHINX_BUILD}
                       # Tell Breathe where to find the Doxygen output
                       -Dbreathe_projects.${PROJECT_NAME}=${DOXYGEN_OUTPUT_DIR}/xml
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   DEPENDS
                       ${DOXYGEN_INDEX_FILE}
                       # Other docs files you want to track should go here (or in some variable)
                       ${DOCUMENTATION_SOURCE}
                   MAIN_DEPENDENCY ${SPHINX_IN} ${SPHINX_OUT}
                   COMMENT "Generating ${PROJECT_NAME} Sphinx documentation")

# Add sphinx target
add_custom_target(Sphinx ALL DEPENDS Doxygen ${SPHINX_INDEX_FILE})
