#ifndef _VARLIB_EVENT_HPP
#define _VARLIB_EVENT_HPP

#include <pthread.h>

namespace varlib {

class event {

public:
  event();
  ~event();

  int signal();
  int reset();
  int wait(long microseconds);

public:
  enum { EVENT_OK, EVENT_FL, EVENT_ET };

private:
  pthread_mutex_t m_mutex_;
  pthread_cond_t m_cond_;
  bool m_notify_;
};

} // namespace varlib

#endif
