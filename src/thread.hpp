
#ifndef _VARLIB_THREAD_HPP
#define _VARLIB_THREAD_HPP

#include "auto_guard.hpp"
#include "event.hpp"
#include "mutex.hpp"
#include "thread_base.hpp"
#include <queue>

namespace varlib {

struct callable {
  void *callable_ptr(void *);
  void *callable_parg;
};

class thread : public varlib::thread_base {
public:
  thread(std::string name = "default") : m_name_(name), m_bstop(false){};

  virtual int run();

  bool addTask(callable call);
  bool delTask(callable call);

  std::string &get_thread_name() { return m_name_; }

private:
  std::string m_name_;
  std::queue<callable> m_queue_;
  varlib::mutex m_mutex_;
  varlib::event m_ev_;
  bool m_bstop;
};

} // namespace varlib

#endif
