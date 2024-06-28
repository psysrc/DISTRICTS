#include "helpers/CitizenNameGenerator.hpp"
#include "helpers/Filesystem.hpp"
#include <stdexcept>
#include <fstream>

std::vector<std::string> CitizenNameGenerator::names;

std::string CitizenNameGenerator::generateName()
{
    // Read citizen names from file the first time a name is requested
    if (names.empty())
    {
        bool succeeded = populateNamesFromFile();

        if (!succeeded)
            names.push_back("unnamed"); // Add a single default name if an error occurs
    }

    std::string randomName = selectRandomName();

    return randomName;
}

/**
 * Populates `names` from the citizen names file.
 * Returns false if an error occurs.
 */
bool CitizenNameGenerator::populateNamesFromFile()
{
    bool success = false;
    try
    {
        std::ifstream inputStream(Filesystem::executableDirectory + "cfg/citizen_names.txt");

        if (inputStream)
        {
            std::string name;

            while (std::getline(inputStream, name))
            {
                names.push_back(name);
            }

            if (!names.empty())
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
 * Returns a random name from `names`.
 */
const std::string &CitizenNameGenerator::selectRandomName()
{
    if (names.empty())
        throw std::logic_error("Can't select random citizen name from an empty set");

    const size_t randomIndex = std::rand() % names.size();
    return names[randomIndex];
}
