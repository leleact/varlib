#ifndef _VARLIB_LOG_LOG_HPP
#define _VARLIB_LOG_LOG_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include <log/config.hpp>
#include <auto_guard.hpp>
#include <string>

namespace varlib {
VARLIB_LOG_NAMESPACE_BEGIN

enum log_level {
    LOG_DBG,
    LOG_INF,
    LOG_WAR,
    LOG_ERR,
    LOG_FAT
};

static std::string log_level_name[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

VARLIB_LOG_NAMESPACE_END
}

#endif
