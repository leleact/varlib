#pragma once

#ifndef _VARLIB_SINGLETON_H
#define _VARLIB_SINGLETON_H

#include "varlib.h"

VARLIB_NAMESPACE_BEGIN

template <typename T> class singleton {

public:
  static T &instance() {
    static MemGuard g; // clean up on program end
    if (!_M_instance) {
      _M_instance = new T();
    }
    return *_M_instance;
  }

  singleton(const singleton &) = delete;
  singleton &operator=(const singleton) = delete;

protected:
  singleton(){};
  virtual ~singleton() {}

private:
  static T *_M_instance;

  class MemGuard {
  public:
    ~MemGuard() {
      delete _M_instance;
      _M_instance = nullptr;
    }
  };
};

VARLIB_NAMESPACE_END

#endif
