include(unittest)

add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

cpp_add_test(TEST_NAME auto_guard_test SOURCE_FILE auto_guard_test.cpp)
target_include_directories(auto_guard_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(auto_guard_test var_static)

cpp_add_test(TEST_NAME event_test SOURCE_FILE event_test.cpp)
target_include_directories(event_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(event_test var_static)
