cmake_minimum_required(VERSION 3.0.2)

project(varlib C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src SOURCE_FILES)
include_directories(include)
include_directories(third_party/sqlite3/src)
include_directories(third_party/spdlog/include)

add_library(var_static STATIC ${SOURCE_FILES})
set_target_properties(var_static PROPERTIES OUTPUT_NAME var)
add_library(var_shared SHARED ${SOURCE_FILES})
set_target_properties(var_shared PROPERTIES OUTPUT_NAME var)


enable_testing()
add_subdirectory(test)
add_subdirectory(third_party/sqlite3)
