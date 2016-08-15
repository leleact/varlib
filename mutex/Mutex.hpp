#include <iostream>
#include <pthread.h>
#include <varlib.h>
#ifndef _MUTEX_H
#define _MUTEX_H
BEGIN_NAMESPACE(varlib)
class Mutex
{
public:
	Mutex();
	virtual ~Mutex();
	int lock();	
	int unlock();
	int trylock();

private:
	pthread_mutex_t m_mutex;
};

END_NAMESPACE
#endif
