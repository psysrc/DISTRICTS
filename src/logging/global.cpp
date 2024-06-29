#include "logging/global.hpp"

void glog(const LogLevel level, const std::string& message)
{
    static Logger glogger;

    glogger.log(level, message);
}


void glog_debug(const std::string& msg)
{
    glog(DEBUG, msg);
}

void glog_info(const std::string& msg)
{
    glog(INFO, msg);
}

void glog_warn(const std::string& msg)
{
    glog(WARN, msg);
}

void glog_error(const std::string& msg)
{
    glog(ERROR, msg);
}

void glog_crit(const std::string& msg)
{
    glog(CRIT, msg);
}
