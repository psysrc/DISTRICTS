#ifndef CITIZENNAMEGENERATOR_H_
#define CITIZENNAMEGENERATOR_H_

#include <string>
#include <vector>

class CitizenNameGenerator {
public:
    CitizenNameGenerator() = delete;

    static std::string generateName();

private:
    static bool populateNamesFromFile();
    static const std::string& selectRandomName();

    static std::vector<std::string> names;
};

#endif // CITIZENNAMEGENERATOR_H_