#include <iostream>
#define size_t std::size_t

namespace VA
{
template <typename T>
class share_ptr
{	
public:
	share_ptr(T *);
	share_ptr(const share_ptr &);

	share_ptr &operator=(T *);
	share_ptr &operator=(const share_ptr &);

	T *operator->();
	T operator*();

	share_ptr &operator++();
	share_ptr &operator++(int n);
	share_ptr &operator+(int n);
	share_ptr &operator--();
	share_ptr &operator--(int n);
	share_ptr &operator-(int n);

private:
	T *handle;
	size_t count;
};
};
