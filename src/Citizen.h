#ifndef CITIZEN_H_
#define CITIZEN_H_

class Citizen;

#include <iostream>
#include "Tile.h"

using std::string;

class Citizen {
private:
	Tile* tile;
	string citizenName;
public:
	Citizen(string name);
	Citizen();
	~Citizen();
	void setTile(Tile* tile);
	Tile* getTile();
	District* getDistrict();
	void takeAction();
	string getName();
};

#endif /* CITIZEN_H_ */
