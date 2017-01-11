#ifndef _VARLIB_LOG_FACTORY_HPP
#define _VARLIB_LOG_FACTORY_HPP

#include <varlib.h>
#include <map>
#include <log.hpp>

_VARLIB_BEGIN_NAMESPACE

class log_factory {
public:
    static log_factory &get_instance() {
        static log_factory logFactory;
        return logFactory;
    }

    logger &getlogger(const std::string& name = "root");

private:
    std::map<std::string, logger> m_logger_map;
    thread_pool m_thread_pool;

    log_factory();
    log_factory(const log_factory &);
    log_factory& operator=(const log_factory &);
};

_VARLIB_END_NAMESPACE

#endif

