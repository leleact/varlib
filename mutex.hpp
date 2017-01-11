
#ifndef _VARLIB_MUTEX_HPP
#define _VARLIB_MUTEX_HPP

#include <pthread.h>

namespace varlib {

class mutex {

public:
    mutex()  { pthread_mutex_init   (&m_mutex_, NULL); }
    ~mutex() { pthread_mutex_destroy(&m_mutex_      ); }

    void lock()   { pthread_mutex_lock  (&m_mutex_); }
    void unlock() { pthread_mutex_unlock(&m_mutex_); }

private:
    pthread_mutex_t m_mutex_;

    mutex(const mutex&);
    mutex& operator=(const mutex&);
};

}

#endif
