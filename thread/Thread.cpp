#include <Thread.hpp>
#include <typeinfo>
_VARLIB_BEGIN_NAMESPACE(varlib)
void *pFunc(void *arg)
{
	Thread *p = (Thread *)arg;
	p->run();
	return (void *)0;
}

Thread::~Thread()
{
}

int Thread::start()
{
	return pthread_create(&m_pid, NULL, pFunc, (void *)this);
}

void Thread::exit()
{
	return pthread_exit(&m_ret);
}

void Thread::stop()
{
	return exit();	
}

int Thread::wait_stop()
{
	return pthread_join(m_pid, &m_ret);
}
_VARLIB_END_NAMESPACE
