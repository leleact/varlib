
namespace vl
{
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
}
