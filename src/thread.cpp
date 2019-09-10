
#include "thread.hpp"

namespace varlib {

int thread::run() {

    while(!m_bstop) {
        callable call;
        {
        
        }
        auto_mutex l(m_mutex_);
        if ( !m_queue_.empty() ) {
            call = m_queue_.front();
            m_queue_.pop();
            call.callable_ptr(call.callable_parg);
        } else {
            int rc = m_ev_.wait(3000);
            if (rc == event::EVENT_ET) {
                continue; 
            }
        }
    }

}

}
