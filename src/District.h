#ifndef DISTRICT_H_
#define DISTRICT_H_

#include "Constants.h"
#include "Tile.h"
#include "Citizen.h"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

#define DISTRICT_SIZE 10

class District {
private:
	string name;
	Tile** tiles;
	vector<Citizen*> citizens;
public:
	District();
	District(string name);
	~District();
	void simulate();
	string getName();
};

#endif /* DISTRICT_H_ */
