
#ifndef _VARLIB_THREAD_POOL_HPP
#define _VARLIB_THREAD_POOL_HPP

#include <queue>
#include <string>

namespace varlib {

class thread_pool {

public:
  thread_pool(const std::string &name = "default");

  bool addtask();

private:
  int m_curr_thread_num;
  int m_max_thread_num;

  std::queue<TASK> m_job_queue;

  thread_pool(const thread_pool &);
  thread_pool &operator=(const thread_pool &);
};

} // namespace varlib

#endif
