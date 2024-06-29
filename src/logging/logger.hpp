#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>

class Logger
{
public:
    Logger();
    ~Logger();

    void log(const std::string&);

private:
    std::ofstream logFile;
};

#endif // LOGGER_H_
