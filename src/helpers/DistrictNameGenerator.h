#ifndef DISTRICTNAMEGENERATOR_H_
#define DISTRICTNAMEGENERATOR_H_

#include <string>
#include <vector>

class DistrictNameGenerator
{
public:
    DistrictNameGenerator() = delete;

    static std::string generateName();

private:
    static bool populateNamesFromFile();
    static const std::string &selectRandomBaseName();

    static std::vector<std::string> baseNames;
};

#endif // DISTRICTNAMEGENERATOR_H_
