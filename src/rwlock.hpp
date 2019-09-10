#ifndef _VARLIB_RWLOCK_HPP
#define _VARLIB_RWLOCK_HPP

#include <pthread.h>
#include <varlib.h>

VARLIB_NAMESPACE_BEGIN

class rwlock {
public:
  rwlock() { pthread_rwlock_init(&m_rwlock_, NULL); }
  ~rwlock() { pthread_rwlock_destroy(&m_rwlock_); }

  void rlock() { pthread_rwlock_rdlock(&m_rwlock_); }
  void wlock() { pthread_rwlock_wrlock(&m_rwlock_); }
  void unlock() { pthread_rwlock_unlock(&m_rwlock_); }

private:
  pthread_rwlock_t m_rwlock_;
  rwlock(const rwlock &);
  rwlock &operator=(const rwlock &);
};

VARLIB_NAMESPACE_END

#endif
