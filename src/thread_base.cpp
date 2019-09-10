
#include "thread_base.hpp"


namespace varlib {

void *thread_function(void *arg) {
    thread_base *p = static_cast<thread_base *>(arg);
    p->m_thread_rc = p->run();
    return (void *)&p->m_thread_rc;
}

thread_base::thread_base() : m_thread_rc( -1 ){ }

thread_base::~thread_base() {
#if defined(_DEBUG) || defined(DEBUG)
    std::cout << "(" << __FILE__ << ":" << __LINE__ << ")[" << __PRETTY_FUNCTION__ << "]" << std::endl;
#endif
}

int thread_base::start() {
#if defined(_DEBUG) || defined(DEBUG)
    std::cout << "(" << __FILE__ << ":" << __LINE__ << ")[" << __PRETTY_FUNCTION__ << "] "
        << "type of this is [" << typeid(*this).name() << "]" << std::endl;
#endif
    return pthread_create(&m_pid, NULL, thread_function, this);
}

int thread_base::join() {
    return pthread_join(m_pid, NULL);
}

int thread_base::detach() {
    return pthread_detach(m_pid);
}

int thread_base::stop() {
    return pthread_join(m_pid, NULL);
}

thread_base::thread_id thread_base::get_thread_id() {
    return static_cast<thread_id>(m_pid);
}

int thread_base::get_thread_rc() {
    return m_thread_rc;
}

}
