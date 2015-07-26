#include <Thread.hpp>
_VARLIB_BEGIN_NAMESPACE(varlib)
void *pFunc(void *arg)
{
	Thread *p = (Thread *)arg;
	p->run();
	return (void *)0;
}

int Thread::start()
{
	int nRet = 0;
	nRet = pthread_create(&m_pid, NULL, pFunc, (void *)this);
	if (nRet != 0)
		return nRet;
	nRet = pthread_join(m_pid, NULL);
	if (nRet != 0)
		return nRet;
	return 0;
}
_VARLIB_END_NAMESPACE
