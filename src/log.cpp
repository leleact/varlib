#include <varlib/log.hpp>

bool varlib::log_initialize::initialized = []() {
  spdlog::set_level(spdlog::level::trace);
  return true;
}();
