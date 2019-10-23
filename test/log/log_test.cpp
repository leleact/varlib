#include <gtest/gtest.h>
#include <varlib/log.hpp>

bool varlib::log_initialize::initialized = []() {
  spdlog::set_level(spdlog::level::trace);
  return false;
}();

TEST(log, LOGD) { LOGD("{}", "LOGD"); }

TEST(log, LOGI) { LOGI("{}", "LOGI"); }
