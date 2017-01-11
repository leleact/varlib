#ifndef _VARLIB_LOG_LOG_HPP
#define _VARLIB_LOG_LOG_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include <log/log.hpp>
#include <log/config.hpp>
#include <auto_guard.hpp>
#include <string>

namespace varlib {
VARLIB_LOG_NAMESPACE_BEGIN

class log_sync_stream {
public:
    log_sync_stream(std::ostream& os):m_log_entity_stream(os){ }
    log_sync_stream(const std::string& full_name):
        m_full_name(full_name), m_log_entity_stream(m_full_name.c_str(), std::iostream::app|std::iostream::binary) {}

private:
    log_sync_stream& operator<<(const std::string& string) {
        varlib::auto_mutex m(m_mutex);
        m_log_entity_stream << string;
        return *this;
    }

private:
const    std::string &m_full_name;
    std::ostream &m_log_entity_stream;
    varlib::mutex m_mutex;
};

VARLIB_LOG_NAMESPACE_END
}

#endif
