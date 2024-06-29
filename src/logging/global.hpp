#ifndef GLOBAL_LOGGER_H_
#define GLOBAL_LOGGER_H_

#include "logging/logger.hpp"

void glog_debug(const std::string& msg);
void glog_info(const std::string& msg);
void glog_warn(const std::string& msg);
void glog_error(const std::string& msg);
void glog_crit(const std::string& msg);

#endif // GLOBAL_LOGGER_H_
