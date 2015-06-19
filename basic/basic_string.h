
#ifndef _VARLIB_BEGIN_NAMESPACE
#define _VARLIB_BEGIN_NAMESPACE(x) namespace x {
#endif
#ifndef _VARLIB_END_NAMESPACE
#define _VARLIB_END_NAMESPACE	}
#endif

#define _VARLIB_BEGIN_NAMESPACEVL  _VARLIB_BEGIN_NAMESPACE(vl)
#define _VARLIB_END_NAMESPACEVL    _VARLIB_END_NAMESPACE

_VARLIB_BEGIN_NAMESPACEVL
#ifndef _BASIC_STRING_H
#define _BASIC_STRING_H
template <typename T>
class basic_string {
public:
  basic_string();
  basic_string(const basic_string &);
  basic_string(const T *);
  basic_string &operator=(const basic_string &);

private:
  T *handle;
};
#endif
_VARLIB_END_NAMESPACEVL
