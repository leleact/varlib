include(unittest)

add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

add_subdirectory(log)
add_subdirectory(sqlite)
add_subdirectory(random)
