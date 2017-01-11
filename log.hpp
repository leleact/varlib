#ifndef _VARLIB_LOG_HPP
#define _VARLIB_LOG_HPP
#include <varlib.h>
#include <string>
#include <exception.hpp>
#include <mutex.hpp>
#include <auto_guard.hpp>
#include <sys/time.h>
VARLIB_NAMESPACE_BEGIN

enum log_level {
    DBG,
    INF,
    WAR,
    ERR,
    FAT
};

class log {
private:
    std::string m_file_name;
    FILE* m_fp;
    varlib::mutex m_mutex;
public:
    log(const std::string& file_name)
        :m_file_name(file_name), m_fp(fopen(m_file_name.c_str(), "wr+")) {}
    ~log() {
        if (m_fp != NULL) {
            fclose(m_fp);
        } 
    }
    void write(const std::string& str, int level) {
        varlib::auto_mutex m(m_mutex);
        if( m_fp != NULL) {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            struct tm result;
            localtime_r(&tv.tv_sec, &result);
            char time[128 + 1] = { 0 };
            strptime(time, "%Y-%m-%d %H:%M:%S", &result);
            fprintf(m_fp, "[%s %03d][%s][%ld]", time, (int)tv.tv_usec/1000, get_level_name(level), pthread_self());
            fprintf(m_fp, "%s\n" , str.c_str());
        } else {
            VARLIB_THROW_DEFAULT;
        }
    }
    void debug(const std::string& str) { write(str, DBG); }
    void info (const std::string& str) { write(str, INF); }
    void warn (const std::string& str) { write(str, WAR); }
    void error(const std::string& str) { write(str, ERR); }
    void fatal(const std::string& str) { write(str, FAT); }

private:
    const char* get_level_name(int level) {
        switch(level) {
        case DBG:
           return "DEBUG";
        case INF:
           return "INFO";
        case WAR:
           return "WARN";
        case ERR:
           return "ERROR";
        case FAT:
           return "FATAL";
        default:
           return "";
        }
    }
};


VARLIB_NAMESPACE_END
#endif
