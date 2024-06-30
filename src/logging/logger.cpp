#include "logging/logger.hpp"
#include "helpers/Filesystem.hpp"
#include "logging/levels.hpp"
#include <chrono>
#include <iomanip>

std::string getCurrentTimeRFC3339();

Logger::Logger(LogLevel level)
    : currentLogLevel(level), logFile(Filesystem::executableDirectory + "DISTRICTS.log", std::ios_base::app)
{
}

Logger::~Logger()
{
    logFile.flush();
}

void Logger::log(const LogLevel level, const std::string &message)
{
    if (level >= currentLogLevel)
    {
        logFile
            << getCurrentTimeRFC3339() << '|'
            << logLevelToString(level) << '|'
            << message
            << '\n';
    }
}

std::string getCurrentTimeRFC3339()
{
    const auto now_us = time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
    const auto now_s = time_point_cast<std::chrono::seconds>(now_us);
    const auto micros = now_us - now_s;
    const auto c_now = std::chrono::system_clock::to_time_t(now_s);

    std::stringstream ss;
    ss << std::put_time(std::gmtime(&c_now), "%FT%T")
       << '.' << std::setfill('0') << std::setw(6) << micros.count() << 'Z';
    return ss.str();
}
