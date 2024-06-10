#include "helpers/Filesystem.h"

std::string Filesystem::executableDirectory;

void Filesystem::initialise(const std::string &executablePath)
{
    /**
     * Example: executablePath is "Desktop/DISTRICTS/game/DISTRICTS"
     * Resulting executableDirectory is "Desktop/DISTRICTS/game/"
     *
     * Example: executablePath is "./DISTRICTS"
     * Resulting executableDirectory is "./"
     */
    const std::string executableName = "DISTRICTS";
    executableDirectory = executablePath.substr(0, executablePath.length() - executableName.length());
}
