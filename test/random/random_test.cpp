#include <gtest/gtest.h>
#include <varlib/random.hpp>

TEST(random, uniform_int) {
  varlib::random<int> r{1, 10};
  int res = r.rand();
  ASSERT_LE(res, 10);
}

TEST(random, uniform_long) {
  varlib::random<long> r{1L, 10L};
  long res = r.rand();
  ASSERT_LE(res, 10L);
}

TEST(random, uniform_double) {
  varlib::random<double, std::uniform_real_distribution> r{1.0, 10.0};
  double res = r.rand();
  ASSERT_LE(res, 10.0);
}

// TEST(random, normal_int) {
// varlib::random<int, std::normal_distribution> r{100, 10};
// int res = r.rand();
//}

// TEST(random, normal_long) {
// varlib::random<long, std::normal_distribution> r{100L, 10L};
// long res = r.rand();
//}

TEST(random, normal_double) {
  varlib::random<double, std::normal_distribution> r{5.0, 1.2};
  double res = r.rand();
}
