#ifndef DISTRICT_H_
#define DISTRICT_H_

class District;

#include "Constants.h"
#include "Citizen.h"
#include "Tile.h"
#include <vector>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

#define DISTRICT_SIZE 16

class District {
private:
	string districtName;
	Tile** tiles;
	vector<Citizen*> citizens;
public:
	District();
	District(const string name);
	~District();
	void simulate();
	string draw();
	string getName();
	Tile** getTiles();
	Tile* getTile(const int i, const int j);
};

#endif /* DISTRICT_H_ */
