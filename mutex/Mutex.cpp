#include <Mutex.hpp>
_VARLIB_BEGIN_NAMESPACE(varlib)
Mutex::Mutex()
{
	if (pthread_mutex_init(&m_mutex, NULL))
	{
		throw std::string("pthread_mutex_init error");	
	}
}

Mutex::~Mutex()
{
	if (pthread_mutex_destroy(&m_mutex))
	{
		throw std::string("pthread_mutex_destroy error");	
	}
}

int Mutex::lock()
{
	return pthread_mutex_lock(&m_mutex);
}

int Mutex::unlock()
{
	return pthread_mutex_unlock(&m_mutex);
}

int Mutex::trylock()
{
	return pthread_mutex_trylock(&m_mutex);
}
_VARLIB_END_NAMESPACE
