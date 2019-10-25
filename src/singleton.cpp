#include <varlib/singleton.hpp>

template <typename T> T *varlib::singleton<T>::_M_instance = nullptr;
