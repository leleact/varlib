#include <iostream>
#include <pthread.h>
#include <varlib.h>
#ifndef _THREAD_H
#define _THREAD_H
_VARLIB_BEGIN_NAMESPACE(varlib)
class Thread
{
friend void *pFunc(void *arg);
public:
	virtual ~Thread();
	int start();
	int wait_stop();
	virtual long run() = 0;
	pthread_t GetThreadId() { return m_pid; };
private:
	pthread_t m_pid;
	void *m_ret;
};
_VARLIB_END_NAMESPACE
#endif
