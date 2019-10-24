#pragma once

#ifndef _VARLIB_LOG_H
#define _VARLIB_LOG_H

#include "varlib/varlib.h"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>

#define LOGT(...) SPDLOG_TRACE(__VA_ARGS__)
#define LOGD(...) SPDLOG_DEBUG(__VA_ARGS__)
#define LOGI(...) SPDLOG_INFO(__VA_ARGS__)
#define LOGW(...) SPDLOG_WARN(__VA_ARGS__)
#define LOGE(...) SPDLOG_ERROR(__VA_ARGS__)

VARLIB_NAMESPACE_BEGIN

class log_initialize {
public:
  static bool initialized;

private:
  log_initialize(){};
  log_initialize(const log_initialize &) = delete;
  log_initialize &operator=(const log_initialize &) = delete;
};

VARLIB_NAMESPACE_END

#endif
