set(TEST_NAME "test_${PROJECT_NAME}")
add_executable(${TEST_NAME} "${TEST_NAME}.cpp")
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

# Local builds of upstream projects require local include paths
if(NOT tardigrade_vector_tools_FOUND)
    target_include_directories(${TEST_NAME} PRIVATE
                               ${tardigrade_vector_tools_SOURCE_DIR}/${CPP_SRC_PATH}
                               ${tardigrade_error_tools_SOURCE_DIR}/${CPP_SRC_PATH})
endif()

get_target_property(target_sources ${TEST_NAME} SOURCES)
foreach(source ${target_sources})
    set_property(GLOBAL APPEND PROPERTY CLANG_FORMAT_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${source}")
endforeach(source)
