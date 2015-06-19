#ifndef _VARLIB_BEGIN_NAMESPACE
#define _VARLIB_BEGIN_NAMESPACE(x) namespace x {
#endif
#ifndef _VARLIB_END_NAMESPACE
#define _VARLIB_END_NAMESPACE	}
#endif

#define _VARLIB_BEGIN_NAMESPACEVL  _VARLIB_BEGIN_NAMESPACE(vl)
#define _VARLIB_END_NAMESPACEVL    _VARLIB_END_NAMESPACE

_VARLIB_BEGIN_NAMESPACEVL
namespace date
{
#ifndef _DATE_H
#define _DATE_H
#include <time.h>
class Date
{
public:
	Date();
	Date(time_t);
	Date(const Date &);
	Date(Date &&);
	Date &operator=(const Date &);

	int GetYear() {return _M_Year;}
	int GetMonth() {return _M_Month;}
	int GetDay() {return _M_Day;}
private:
	int _M_Year;
	int _M_Month;
	int _M_Day;
};
#endif
}
_VARLIB_END_NAMESPACEVL
