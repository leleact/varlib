#include <iostream>
#include <pthread.h>
#include <varlib.h>
#ifndef _EVENT_H
#define _EVENT_H
_VARLIB_BEGIN_NAMESPACE(varlib)
class Event
{
public:
	Event(bool bInit = false);
	~Event();
	int wait();
	int set();
	int reset();
private:
	Event(const Event &);
	Event &operator=(Event &);
private:
	bool m_bNotify;
	pthread_cond_t m_Cond;
	pthread_mutex_t m_Mutex;
};
_VARLIB_END_NAMESPACE
#endif
