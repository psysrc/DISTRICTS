#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>
#include "logging/levels.hpp"

class Logger
{
public:
    Logger(LogLevel);
    ~Logger();

    void log(const LogLevel level, const std::string&);

private:
    LogLevel currentLogLevel;
    std::ofstream logFile;
};

#endif // LOGGER_H_
