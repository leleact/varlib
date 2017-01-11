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

class log_syn_stream {
public:
    static log_syn_stream& getInstance(const std::string& full_name) {
        static log_syn_stream l(full_name); 
        return l;
    }
private:
    log_syn_stream(const std::string& full_name):
        m_full_name(full_name), m_log_entity_stream(m_full_name.c_str(), std::iostream::app|std::iostream::binary) {}

private:
    log_syn_stream& operator<<(const std::string& string) {
        varlib::auto_mutex m(m_mutex);
        m_log_entity_stream << string;
        return *this;
    }

private:
    std::string m_full_name;
    std::ofstream m_log_entity_stream;
    varlib::mutex m_mutex;
};

VARLIB_LOG_NAMESPACE_END
}

#endif
