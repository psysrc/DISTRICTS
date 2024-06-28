#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <string>

class Filesystem
{
public:
    static void initialise(const std::string &executablePath);
    static std::string executableDirectory;
};

#endif // FILESYSTEM_H_
