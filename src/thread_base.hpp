
#ifndef _VARLIB_THREAD_BASE_HPP
#define _VARLIB_THREAD_BASE_HPP

#include <iostream>
#include <pthread.h>
#include <typeinfo>

namespace varlib {

class thread_base {
  friend void *thread_function(void *);

public:
  typedef long thread_id;
  thread_base();
  ~thread_base();
  virtual int start();
  int join();
  int detach();
  bool is_detachable();
  virtual int stop();
  virtual int run() = 0;

  thread_id get_thread_id();
  int get_thread_rc();

private:
  pthread_t m_pid;
  int m_thread_rc;
  thread_base(const thread_base &);
  thread_base &operator=(const thread_base &);
};

} // namespace varlib

#endif
