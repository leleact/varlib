cmake_minimum_required(VERSION 3.0.2)

project(varlib C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_VERBOSE_MAKEFILE ON)

AUX_SOURCE_DIRECTORY(src SOURCE_FILES)
include_directories(include)
ADD_LIBRARY(var ${SOURCE_FILES})

enable_testing()
add_subdirectory(test)
