


#ifndef _AUTO_GUARD_H
#define _AUTO_GUARD_H

#include <pthread.h>

namespace varlib {

template<typename Lock,void (Lock::*lock_func)(), void (Lock::*unlock_func)()>
class AutoGuard {
public:
    AutoGuard(Lock &lock):m_lock(lock) {
        (m_lock.*lock_func)();
    }
    ~AutoGuard() {
        (m_lock.*unlock_func)(); 
    }
private:
    Lock &m_lock;
};

class Mutex {
public:
    Mutex() {
        pthread_mutex_init(&m_Mutex, NULL);
    }

    void lock() {
        pthread_mutex_lock(&m_Mutex); 
    }

    void unlock() {
        pthread_mutex_unlock(&m_Mutex);
    }

    ~Mutex() {
        pthread_mutex_destroy(&m_Mutex); 
    }

    Mutex(const Mutex &) = delete;
    Mutex& operator=(const Mutex &) = delete;
private:
    mutable pthread_mutex_t m_Mutex;
};

}


#endif
