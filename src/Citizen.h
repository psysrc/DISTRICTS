#ifndef CITIZEN_H_
#define CITIZEN_H_

#include <iostream>

using std::string;

class Citizen {
private:
	string name;
public:
	Citizen(string name);
	Citizen();
	~Citizen();
	void takeAction();
	string getName();
};

#endif /* CITIZEN_H_ */
