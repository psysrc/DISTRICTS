#include "logging/global.hpp"

void glog(const std::string& message)
{
    static Logger glogger;

    glogger.log(message);
}
