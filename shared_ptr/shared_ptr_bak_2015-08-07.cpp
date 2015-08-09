#include <iostream>
namespace varlib
{
template <typename T>
class shared_ptr;

template <typename T>
class Ref
{
	friend class shared_ptr<T>;
public:
	Ref(int nRef) : m_nRef(nRef) {}
private:
	int m_nRef;
};

template <typename T>
class shared_ptr
{
public:
	shared_ptr(T *Ptr) : m_Ptr(Ptr), m_Ref(new Ref<T>(1)) {}
	shared_ptr(const shared_ptr &Ptr) : m_Ptr(Ptr.m_Ptr), m_Ref(Ptr.m_Ref)
	{
		m_Ref->m_nRef++;
	}
	shared_ptr &operator=(const shared_ptr &Ptr)
	{
		Ptr.m_Ref->m_nRef++;
		if (--m_Ref->m_nRef == 0)
		{
			delete m_Ptr;
		}
		m_Ptr = Ptr.m_Ptr;
		m_Ref = Ptr.m_Ref;
	}
	~shared_ptr()
	{
		if (--m_Ref->m_nRef == 0)	
		{
			delete m_Ptr;	
		}
	}

private:
	T *m_Ptr;
	Ref<T> *m_Ref;
};
}
