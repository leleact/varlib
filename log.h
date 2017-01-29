#ifndef _VARLIB_LOG_H
#define _VARLIB_LOG_H

#include <varlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <mutex>
#include <map>
#include <unistd.h>
#include <sys/time.h>

VARLIB_NAMESPACE_BEGIN

enum log_level { DBG, INF, WAR, ERR, FAT };

class log;
const log_level DEFAULT_LEVEL   = INF;
const long      DEFAULT_LOG_LEN = 100 * 1024 * 1024;

class log_factory {
public:
    log_factory();
    log_factory(const long& log_mex_len, const log_level& log_level);
    log& getLogger(const std::string &log_name, const log_level& level);
    log& getLogger(const char*       pLogname, const log_level& level);

    ~log_factory();

private:

    /* delete copy constructor and asign operator */
    log_factory(const log_factory&);
    log_factory& operator=(const log_factory&);

private:
    std::map<std::string, log*> m_logs;
    const long&                 m_log_mex_len;
    const log_level&            m_log_level;
};

static log_factory logger;

class log {
public:
    log();
    log(const std::string& name, const log_level& level = DEFAULT_LEVEL);
    log(const std::string& log_name, const std::string& log_date,
            const int& log_index, const long& file_max_len,
            const log_level& log_level);

    long debug(const std::string& event) {
        if ( m_log_level <= DBG)
            return write(event, DBG);
        return 0;
    }
    long info (const std::string& event) {
        if ( m_log_level <= INF )
            return write(event, INF);
        return 0;
    }
    long warn (const std::string& event) {
        if ( m_log_level <= WAR )
            return write(event, WAR);
        return 0;
    }
    long error(const std::string& event) {
        if ( m_log_level <= ERR )
            return write(event, ERR);
        return 0;
    }
    long fatal(const std::string& event) {
        if ( m_log_level <= FAT )
            return write(event, FAT);
        return 0;
    }

private:
   log(const log&);
   log& operator=(const log&);

   long write(const std::string& event, log_level level);
   std::string getCurrDate();
   std::string getLogFileName();
   void initialization();

private:
    std::string m_log_name;
    std::string m_log_date;
    int         m_log_index;

    std::string m_log_file_name;
    FILE*       m_file_ptr;
    std::mutex  m_file_mutex;
    long        m_file_max_len;

    long        m_file_curr_len;
    log_level   m_log_level;
};

/**
 * 输出日志名称 name.{YYYY-MM-DD}.index.log
 */

/*
class log {
    friend class log_factory;
private:
    std::string m_prefix_name;
    int m_index;

    std::string m_file_name;

    FILE* m_fp;
    std::mutex m_mutex;

    long m_max_file_len;
public:
    log() {}
    log(const std::string& name) : m_prefix_name(name), m_index(0), m_fp(NULL),
        m_max_file_len( 100 * 1024 * 1024 ) {
            while( 1 ) {
                std::string now;
                getCurrDate( now );
                std::ostringstream os;
                os << m_prefix_name << "." << now << "." << m_index << ".log";
                m_file_name = os.str();
                m_fp = fopen(m_file_name.c_str(), "a+");
                if ( !m_fp ) {
                    // exception
                }
                fseek( m_fp, 0L, SEEK_END );
                long l = ftell( m_fp );
                if ( l >= m_max_file_len ) {
                    fclose( m_fp );
                    m_index++;
                } else {
                    break;
                }
            }
    }
    ~log() {
        if (m_fp != NULL) {
            fclose(m_fp);
        }
    }

    void setfile(const std::string& file) {
        m_file_name = file;
        m_fp = fopen(m_file_name.c_str(), "a+");
    }

    void write(const std::string& str, int level) {
        std::lock_guard<std::mutex> l( m_mutex );
        if( m_fp != NULL) {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            struct tm result;
            localtime_r(&tv.tv_sec, &result);
            char time[100 + 1] = { 0 };
            strftime(time, 100, "%Y-%m-%d %H:%M:%S", &result);
            fprintf(m_fp, "[%s.%03d][%s][%ld]", time, (int)tv.tv_usec/1000, get_level_name(level), pthread_self());
            fprintf(m_fp, "%s\n" , str.c_str());
            fflush(m_fp);
        } else {
            std::cout << "m_fp NULL" << std::endl;
        }
    }
    void debug(const std::string& str) { write(str, DBG); }
    void info (const std::string& str) { write(str, INF); }
    void warn (const std::string& str) { write(str, WAR); }
    void error(const std::string& str) { write(str, ERR); }
    void fatal(const std::string& str) { write(str, FAT); }

private:
    void getCurrDate(std::string &date) {
        time_t now;
        time( &now );
        struct tm ts;
        localtime_r(&now, &ts);
        // YYYY-MM-DD
        char t[10 + 1] = { 0 };
        strftime(t, 100, "%Y-%m-%d %H:%M:%S", &ts);
        date = t;
    }

    bool isExsit(const std::string& filename) {
        int r = access( filename.c_str(), F_OK );
        if ( r )
            return false;
        return true;
    }

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

    log(const log&) { }
    log& operator=(const log&) { return *this; }
};
*/

VARLIB_NAMESPACE_END

#endif
