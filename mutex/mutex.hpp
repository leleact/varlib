#include <iostream>
#include <pthread.h>
#include <varlib.h>
#ifndef _MUTEX_H
#define _MUTEX_H
_VARLIB_BEGIN_NAMESPACE(varlib)
class Mutex
{
	Mutex();
	virtual ~Mutex();
	int lock();	
	int unlock();
	int trylock();

private:
	pthread_mutex_t m_mutex;
};

_VARLIB_END_NAMESPACE
#endif
