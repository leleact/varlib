#include "log.h"
#include <algorithm>
#include <utility>

VARLIB_NAMESPACE_BEGIN

log_factory::log_factory()
    : m_log_mex_len(DEFAULT_LOG_LEN), m_log_level(DEFAULT_LEVEL) {}

log_factory::log_factory(const long &log_mex_len, const log_level &log_level)
    : m_log_mex_len(log_mex_len), m_log_level(log_level) {}

log &log_factory::getLogger(const std::string &log_name,
                            const log_level &level) {
  std::map<std::string, log *>::iterator it = m_logs.find(log_name);
  if (it != m_logs.end()) {
    return *(it->second);
  }

  log *l = new log(log_name, level);
  m_logs.insert(std::make_pair<std::string, log *>(
      std::move(const_cast<std::string &>(log_name)), std::move(l)));
  return *l;
}

log &log_factory::getLogger(const char *pLogname, const log_level &level) {
  const std::string log_name = pLogname;
  return getLogger(log_name, level);
}

log_factory::~log_factory() {
  for_each(
      m_logs.begin(), m_logs.end(),
      [](const std::pair<std::string, log *> &pair) { delete pair.second; });
}

log::log()
    : m_log_name("main"), m_log_date(getCurrDate()), m_log_index(0),
      m_file_ptr(NULL), m_file_max_len(DEFAULT_LOG_LEN), m_file_curr_len(0),
      m_log_level(DEFAULT_LEVEL) {
  initialization();
}

log::log(const std::string &log_name, const log_level &level)
    : m_log_name(log_name), m_log_date(getCurrDate()), m_log_index(0),
      m_file_ptr(NULL), m_file_max_len(DEFAULT_LOG_LEN), m_file_curr_len(0),
      m_log_level(level) {
  initialization();
}

log::log(const std::string &log_name, const std::string &log_date,
         const int &log_index, const long &file_max_len,
         const log_level &log_level)
    : m_log_name(log_name), m_log_date(log_date), m_log_index(log_index),
      m_file_ptr(NULL), m_file_max_len(file_max_len), m_file_curr_len(0),
      m_log_level(log_level) {
  initialization();
}

std::string log::getLogFileName() {
  std::ostringstream os;
  os << m_log_name << "." << m_log_date << "." << m_log_index << ".log";
  return os.str();
}

void log::initialization() {
  while (1) {
    m_log_file_name = getLogFileName();
    m_file_ptr = fopen(m_log_file_name.c_str(), "a+");
    if (!m_file_ptr) {
      // exception
    }
    fseek(m_file_ptr, 0L, SEEK_END);
    long l = ftell(m_file_ptr);
    if (l >= m_file_max_len) {
      fclose(m_file_ptr);
      m_log_index++;
    } else {
      break;
    }
  }
}

VARLIB_NAMESPACE_END
