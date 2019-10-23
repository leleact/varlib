add_executable(log_test log_test.cpp)
target_link_libraries(log_test var_header_only gtest_main spdlog::spdlog_header_only var_static)
add_test(NAME log_test COMMAND log_test)
