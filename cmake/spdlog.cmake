include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
find_path(HEADER_FILE "spdlog/spdlog.h" DOC "spdlog header file")
if (HEADER_FILE)
    message(STATUS "spdlog has been install by the host")
else()
    ExternalProject_Add(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG master
        SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/spdlog-src
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        )
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/spdlog-src/include)
endif()
link_libraries(pthread)
