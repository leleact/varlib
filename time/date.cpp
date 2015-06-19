#include "date.h"
#include <time.h>
_VARLIB_BEGIN_NAMESPACEVL

namespace time
{
Date::Date()
{
	time_t tTime = time(nullptr);
	struct tm *stTm = localtime(&tTime);
	_M_Year = stTm->tm_year + 1900;
	_M_Month = stTm->tm_mon + 1;
	_M_Day = stTm->tm_mday;
}

Date Date::operator=(const Date &d)
{
	_M_Year = d._M_Year;	
	_M_Month = d._M_Month;
	_M_Day = d._M_Day;
	return *this;
}

}


_VARLIB_END_NAMESPACEVL
