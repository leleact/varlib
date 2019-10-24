cmake_minimum_required(VERSION 3.0.2)

project(varlib C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

aux_source_directory(src VARLIB_SOURCE_FILES)

add_library(var_static STATIC ${VARLIB_SOURCE_FILES})
target_link_libraries(var_static spdlog::spdlog_header_only var_header_only)
set_target_properties(var_static PROPERTIES OUTPUT_NAME var)

add_library(var_shared SHARED ${VARLIB_SOURCE_FILES})
target_link_libraries(var_shared spdlog::spdlog_header_only var_header_only)
set_target_properties(var_shared PROPERTIES OUTPUT_NAME var)

add_library(var_header_only INTERFACE)
target_include_directories(var_header_only INTERFACE include)
target_link_libraries(var_header_only INTERFACE spdlog::spdlog_header_only sqlite3_header_only sqlite3_shared)

enable_testing()
add_subdirectory(test)
add_subdirectory(third_party/sqlite3)
add_subdirectory(third_party/spdlog)
