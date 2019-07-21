#ifndef CITIZEN_H_
#define CITIZEN_H_

#include <iostream>

class Citizen {
private:
	std::string name;
public:
	Citizen(std::string name);
	Citizen();
	~Citizen();
	void takeAction();
	std::string toString();
};

#endif /* CITIZEN_H_ */
