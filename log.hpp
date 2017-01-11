#ifndef _VARLIB_LOG_HPP
#define _VARLIB_LOG_HPP

#include <varlib.h>
#include <string>
#include <map>
#include <queue>

_VARLIB_NAMESPACE_BEGIN

class log {
public:
    log(const std::string &name) : m_name(name) { };
    log(const log&l) { }
    log(log&& l) { }
    log& operator=(const log&) { }
    log& operator=(log&& rfo) { }
    ~log() { }

public:
    const std::string& get_log_name() const { return m_name; }
    bool write(const char *, std::size_t len);

private:
    std::string m_name;
    std::queue<std::string> m_queue;
};

_VARLIB_NAMESPACE_END


#endif
