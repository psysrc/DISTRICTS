#include "logging/logger.hpp"
#include "helpers/Filesystem.hpp"

Logger::Logger() : logFile(Filesystem::executableDirectory + "DISTRICTS.log")
{

}

Logger::~Logger()
{
    logFile.flush();
}

void Logger::log(const std::string& message)
{
    logFile << message << '\n';
}
