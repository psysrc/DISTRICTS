#ifndef LOG_LEVELS_H_
#define LOG_LEVELS_H_

#include <string>

enum LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR,
    CRIT,
};

std::string logLevelToString(LogLevel);

#endif // LOG_LEVELS_H_
