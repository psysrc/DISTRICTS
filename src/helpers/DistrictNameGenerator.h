#ifndef DISTRICTNAMEGENERATOR_H_
#define DISTRICTNAMEGENERATOR_H_

#include <string>
#include <vector>

class DistrictNameGenerator {
public:
    DistrictNameGenerator() = delete;

    static std::string generateName();

private:
    static void populateNamesFromFile();

    static std::vector<std::string> knownNames;
};

#endif // DISTRICTNAMEGENERATOR_H_