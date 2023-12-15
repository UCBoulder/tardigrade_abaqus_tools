set(TEST_NAME "test_${PROJECT_NAME}")
add_executable(${TEST_NAME} "${TEST_NAME}.cpp")
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

# Local builds of upstream projects require local include paths
if(NOT tardigrade_vector_tools_FOUND)
    target_include_directories(${TEST_NAME} PRIVATE
                               "${tardigrade_vector_tools_SOURCE_DIR}/src/cpp",
                               "${tardigrade_error_tools_SOURCE_DIR}/src/cpp")
endif()
