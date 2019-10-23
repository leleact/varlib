add_library(sqlite3_header_only INTERFACE)
target_include_directories(sqlite3_header_only INTERFACE src)

add_library(sqlite3_static STATIC src/sqlite3.c)
set_target_properties(sqlite3_static PROPERTIES OUTPUT_NAME sqlite3)
target_link_libraries(sqlite3_static pthread dl)

add_library(sqlite3_shared SHARED src/sqlite3.c)
set_target_properties(sqlite3_shared PROPERTIES OUTPUT_NAME sqlite3)
target_link_libraries(sqlite3_shared pthread dl)

add_executable(sqlite3_bin src/shell.c)
set_target_properties(sqlite3_bin PROPERTIES OUTPUT_NAME sqlite3)
target_link_libraries(sqlite3_bin sqlite3_static)
