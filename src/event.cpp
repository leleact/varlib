#include "event.hpp"
#include <iostream>

namespace varlib {

event::event() : m_notify_(true) {
  pthread_cond_init(&m_cond_, NULL);
  pthread_mutex_init(&m_mutex_, NULL);
}

event::~event() {
  pthread_cond_destroy(&m_cond_);
  pthread_mutex_destroy(&m_mutex_);
}

int event::signal() {
  pthread_mutex_lock(&m_mutex_);
  m_notify_ = false;
  pthread_mutex_unlock(&m_mutex_);
  pthread_cond_broadcast(&m_cond_);
  return 0;
}

int event::reset() {
  pthread_mutex_lock(&m_mutex_);
  m_notify_ = true;
  pthread_mutex_unlock(&m_mutex_);
  return 0;
}

int event::wait(long microseconds) {
  pthread_mutex_lock(&m_mutex_);
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  ts.tv_sec += microseconds / 1000;
  ts.tv_nsec += (microseconds % 1000) * 1000000;
  int rc = 0;
  while (m_notify_ && rc == 0) {
    rc = pthread_cond_timedwait(&m_cond_, &m_mutex_, &ts);
  }
  if (rc == 0)
    m_notify_ = true;
  pthread_mutex_unlock(&m_mutex_);
  switch (rc) {
  case ETIMEDOUT:
    return EVENT_ET;
  case 0:
    return EVENT_OK;
  default:
    return EVENT_FL;
  }
  return 0;
}

} // namespace varlib
