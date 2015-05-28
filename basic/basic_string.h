
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

private:
  T *handle;
};
#endif
}
