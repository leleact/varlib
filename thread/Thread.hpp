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
	virtual int start();
	virtual long run() = 0;
private:
	pthread_t m_pid;
};
_VARLIB_END_NAMESPACE
#endif
