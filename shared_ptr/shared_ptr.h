#include <iostream>
#define size_t std::size_t

namespace VACP
{

template <typename T> class shared_ptr;
template <typename T> class refcount;

template <typename T> class refcount
{
	friend class shared_ptr<T>;
	refcount() : _M_Count(1)
	{
	}

	refcount(size_t __Count) : _M_Count(__Count)
	{
	}

	refcount(const refcount & other) : _M_Count(other._M_Count)
	{
		other._M_Count = other._M_Count + 1;
		_M_Count = _M_Count + 1;
	}

	~refcount()
	{
		_M_Count--;	
	}

	size_t _M_Count;
};

template <typename T>
class shared_ptr
{
	friend class shared_ptr<T>;
public:
	shared_ptr(T *__Ptr) : _M_TPtr(__Ptr), _M_Refcount(1)
	{
	}

	shared_ptr(const shared_ptr &__Ptr) : _M_TPtr(__Ptr._M_TPtr), _M_Refcount(__Ptr._M_Refcount)
	{
	}

	shared_ptr &operator=(const shared_ptr & __Ptr)
	{
		if(_M_TPtr != __Ptr._M_TPtr)
		{
			__Ptr._M_Refcount._M_Count++;
			if (--_M_Refcount._M_Count <= 0)
			{
				delete _M_TPtr;	
			}
			_M_Refcount._M_Count = __Ptr._M_Refcount._M_Count;
			_M_TPtr = __Ptr._M_TPtr;
		}
		return *this;
	}

	~shared_ptr()
	{
		if(--_M_Refcount._M_Count <= 0)	
		{
			delete _M_TPtr;	
		}
	}

	shared_ptr &operator=(const T *__Ptr)
	{
		if (_M_TPtr == __Ptr)
			return *this;
		if (--_M_Refcount <= 0)	
		{
			delete _M_TPtr;	
		}
		_M_Refcount = 1;
		_M_TPtr = __Ptr;

		return *this;
	}

	T *operator->();
	T operator*();

	shared_ptr &operator++();
	shared_ptr &operator++(int n);
	shared_ptr &operator+(int n);
	shared_ptr &operator--();
	shared_ptr &operator--(int n);
	shared_ptr &operator-(int n);

	bool operator==(shared_ptr &);
	bool operator!=(shared_ptr &);

private:
	T * _M_TPtr;
	refcount<T> _M_Refcount;
};
};
