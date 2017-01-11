
#include <iostream>
#include "auto_guard.hpp"
#include "thread_base.hpp"
#include <cstdlib>

class CThread : public varlib::thread_base {
public:
    CThread(long &i, varlib::rwlock &rw) : m_count(i), m_rw_lock(rw) {
        std::cout << "(" << __FILE__ << ":" << __LINE__ << ")[" << __PRETTY_FUNCTION__ << "]" << std::endl;
    }

    int run() {
        std::cout << "(" << __FILE__ << ":" << __LINE__ << ")[" << __PRETTY_FUNCTION__ << "] "
            << "m_count[" << m_count << "] tid[" << this->get_thread_id() << "]" << std::endl;
        while(1) {
            varlib::auto_wlock l(m_rw_lock);
            if (m_count % 10000 == 0) {
               std::cout << "(" << __FILE__ << ":" << __LINE__ << ")[" << __PRETTY_FUNCTION__ << "] "
                   << "m_count[" << m_count << "] tid[" << this->get_thread_id() << "]" << std::endl;
            }
            if (m_count <= 0)
                 break;
            m_count--;
        }
    }

private:
    long &m_count;
    varlib::rwlock &m_rw_lock;

};

int main(int argc, char *argv[]) {
    varlib::rwlock rwlock;
    long count = 0;
    if (argc >= 2)
        count = std::atol(argv[1]);
    else
        count = 1000000;

    CThread c(count, rwlock);
    CThread d(count, rwlock);
    c.start();
    d.start();
    c.join();
    d.join();
    std::cout << "(" << __FILE__ << ":" << __LINE__ << ")[" << __PRETTY_FUNCTION__ << "] "
        << "count[" << count << "]" << std::endl;

    return 0;
}
