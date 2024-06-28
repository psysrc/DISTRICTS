#include "helpers/DistrictNameGenerator.hpp"
#include "helpers/Filesystem.hpp"
#include <stdexcept>
#include <cstdlib>
#include <fstream>

std::vector<std::string> DistrictNameGenerator::baseNames;

std::string DistrictNameGenerator::generateName()
{
    // Read district base names from file the first time a name is requested
    if (baseNames.empty())
    {
        bool succeeded = populateNamesFromFile();

        if (!succeeded)
            baseNames.push_back("unnamed"); // Add a single default name if an error occurs
    }

    std::string randomName = selectRandomBaseName();

    return randomName;
}

/**
 * Populates `baseNames` from the district names file.
 * Returns false if an error occurs.
 */
bool DistrictNameGenerator::populateNamesFromFile()
{
    bool success = false;
    try
    {
        std::ifstream inputStream(Filesystem::executableDirectory + "cfg/district_names.txt");

        if (inputStream)
        {
            std::string name;

            while (std::getline(inputStream, name))
            {
                baseNames.push_back(name);
            }

            if (!baseNames.empty())
                success = true;

            inputStream.close();
        }
    }
    catch (std::exception &ex)
    {
    }

    return success;
}

/**
 * Returns a random name from `baseNames`.
 */
const std::string &DistrictNameGenerator::selectRandomBaseName()
{
    if (baseNames.empty())
        throw std::logic_error("Can't select random district base name from an empty set");

    const size_t randomIndex = std::rand() % baseNames.size();
    return baseNames[randomIndex];
}
