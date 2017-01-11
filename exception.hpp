
#ifndef _VARLIB_EXCEPTION_HPP
#define _VARLIB_EXCEPTION_HPP

#include <stdexcept>
#include <sstream>
#include <string>
#include <cstring>
#include <cerrno>

namespace varlib {

class exception : public std::exception {

public:
    exception() : m_file_(""), m_line_(0), m_func_(""), m_mess_(""),m_errno_(errno) { build_what_message(); }
    exception(const std::string& _Msg) : m_file_(""), m_line_(0), m_func_(""), m_mess_(_Msg), m_errno_(errno) { build_what_message(); }
    exception(const std::string& _file, const std::size_t& _line)
        : m_file_(_file), m_line_(_line), m_func_(""), m_mess_(""), m_errno_(errno) { build_what_message(); }
    exception(const std::string& _file, const std::size_t& _line, const std::string& _func)
        : m_file_(_file), m_line_(_line), m_func_(_func), m_mess_(""), m_errno_(errno) { build_what_message(); }
    exception(const std::string& _file, const std::size_t& _line, const std::string& _func, const std::string& _message)
        : m_file_(_file), m_line_(_line), m_func_(_func), m_mess_(_message), m_errno_(errno) { build_what_message(); }

    virtual const char *what() const noexcept override {
        return m_message.c_str();
    }

private:

    const std::string& m_file_;
    const std::size_t& m_line_;
    const std::string& m_func_;
    const std::string& m_mess_;
    const int&         m_errno_;
    std::string m_message;

    void build_what_message() {
        std::ostringstream os;
        if (m_file_.length() != 0 && m_line_ != 0)
            os << "[" << m_file_ << ":" << m_line_ << "]";
        if (m_func_.length() != 0)
            os << "[" << m_func_ << "]";
        if (m_mess_.length() != 0)
            os << "[" << m_mess_ << "]";
        if (m_errno_ !=0)
            os << "[" << m_errno_ << ":" << strerror(m_errno_) << "]";
        m_message = os.str();
    }
};

}

#define VARLIB_THROW_DEFAULT { throw varlib::exception(__FILE__, __LINE__, __PRETTY_FUNCTION__); }
#define VARLIB_THROW_COND(c)\
    if (c) {\
        VARLIB_THROW_DEFAULT\
    }
#define VARLIB_THROW_COND_MSG(c, m)\
    if (c) {\
        throw varlib::exception(__FILE__, __LINE__, __PRETTY_FUNCTION__, m);\
    }

#endif
