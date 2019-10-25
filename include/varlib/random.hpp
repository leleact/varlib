#pragma once

#ifndef _VARLIB_RANDOM_H
#define _VARLIB_RANDOM_H

#include "varlib.h"
#include <random>

VARLIB_NAMESPACE_BEGIN

template <typename T, template <class> class D = std::uniform_int_distribution>
struct random {
  random(const T &min, const T &max) : _M_min(min), _M_max(max) {}
  T rand() {
    static std::random_device rd{};
    static std::mt19937 gen{rd()};
    static D<T> dis(_M_min, _M_max);
    return dis(gen);
  }

private:
  T _M_min;
  T _M_max;
};

template <typename T> struct random<T, std::normal_distribution> {
  random(const T &mean, const T &stddev) : _M_mean(mean), _M_stddev(stddev) {}
  T rand() {
    static std::random_device rd{};
    static std::mt19937 gen{rd()};
    static std::normal_distribution<T> dis(_M_mean, _M_stddev);
    return dis(gen);
  }

private:
  T _M_mean;
  T _M_stddev;
};

VARLIB_NAMESPACE_END

#endif
