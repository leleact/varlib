#include <Thread.hpp>

namespace varlib
{
void *pFunc(void *arg)
{
	Thread *p = (Thread *)arg;
	p->run();
	return (void *)0;
}

void Thread::start()
{
	pthread_create(&m_pid, NULL, pFunc, (void *)this);
	pthread_join(m_pid, NULL);
}
}
