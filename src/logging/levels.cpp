#include "logging/levels.hpp"
#include <stdexcept>

std::string logLevelToString(LogLevel level)
{
    switch (level)
    {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case ERROR:
            return "ERROR";
        case CRIT:
            return "CRIT";

        default:
            throw std::runtime_error("Failed to convert log level to string: " + std::to_string(level));
    }
}
