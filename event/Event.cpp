#include <Event.hpp>
_VARLIB_BEGIN_NAMESPACE(varlib)
Event::Event(bool bInit)
{
	if (pthread_cond_init(&m_Cond, NULL))
	{
		throw std::string("pthread_cond_init error");	
	}

	if (pthread_mutex_init(&m_Mutex, NULL))
	{
		throw std::string("pthread_mutex_init error");	
	}
	m_bNotify = bInit;
}

Event::~Event()
{
	if (pthread_cond_destroy(&m_Cond))
	{
		throw std::string("pthread_cond_destroy error");	
	}

	if (pthread_mutex_destroy(&m_Mutex))
	{
		throw std::string("pthread_mutex_destroy error");	
	}
}

int Event::wait()
{
	int nRet = 0;
	nRet = pthread_mutex_lock(&m_Mutex);
	if (nRet)
	{
		return nRet;	
	}

	while(m_bNotify)
	{
		nRet = pthread_cond_wait(&m_Cond, &m_Mutex);
		if (nRet)
		{
			return nRet;
		}
	}

	nRet = pthread_mutex_unlock(&m_Mutex);
	if (nRet)
	{
		return nRet;	
	}
	return nRet;	
}

int Event::set()
{
	int nRet = 0;
	nRet = pthread_mutex_lock(&m_Mutex);
	if (nRet)
	{
		return nRet;	
	}
	m_bNotify = true;
	nRet = pthread_mutex_unlock(&m_Mutex);
	if (nRet)
	{
		return nRet;	
	}
	return pthread_cond_broadcast(&m_Cond);
}

int Event::reset()
{
	int nRet = 0;
	nRet = pthread_mutex_lock(&m_Mutex);
	if (nRet)
	{
		return nRet;	
	}
	m_bNotify = false;
	nRet = pthread_mutex_unlock(&m_Mutex);
	if (nRet)
	{
		return nRet;	
	}
	return 0;
}
_VARLIB_END_NAMESPACE
