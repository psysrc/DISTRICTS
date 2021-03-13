#include "helpers/DistrictNameGenerator.h"

std::vector<std::string> DistrictNameGenerator::knownNames;

std::string DistrictNameGenerator::generateName()
{
    if (knownNames.empty())
    {
        populateNamesFromFile();
    }

    return knownNames.at(0);
}

/**
 * Populates `knownNames` from the district names file.
 */
void DistrictNameGenerator::populateNamesFromFile()
{
    // TODO

    knownNames.push_back("unnamed");
}