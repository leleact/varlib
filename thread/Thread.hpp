#include <iostream>
#include <pthread.h>

namespace varlib
{
#ifndef _THREAD_H
#define _THREAD_H
class Thread
{
friend void *pFunc(void *arg);
public:
	void start();
	virtual long run() = 0;
private:
	pthread_t m_pid;
};
#endif


}
