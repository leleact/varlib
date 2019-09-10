
#ifndef _VARLIB_AOTU_GUARD_HPP
#define _VARLIB_AOTU_GUARD_HPP

#include "mutex.hpp"
#include "rwlock.hpp"

namespace varlib {

template <typename _Lock, void (_Lock::*lock)(), void (_Lock::*unlock)()>
class auto_guard {

public:
  auto_guard(_Lock &_l) : m_lock(_l) { (m_lock.*lock)(); }

  ~auto_guard() { (m_lock.*unlock)(); }

private:
  _Lock &m_lock;
};

typedef auto_guard<rwlock, &rwlock::rlock, &rwlock::unlock> auto_rlock;
typedef auto_guard<rwlock, &rwlock::wlock, &rwlock::unlock> auto_wlock;
typedef auto_guard<mutex, &mutex::lock, &mutex::unlock> auto_mutex;

} // namespace varlib

#endif
