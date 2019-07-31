#ifndef CITIZEN_H_
#define CITIZEN_H_

class Citizen;

#include <string>
#include "Tile.h"

using std::string;

class Citizen {
private:
	Tile* pTile;
	string citizenName;
public:
	Citizen(const string name);
	Citizen();
	~Citizen();
	void setTile(Tile* tile);
	Tile* getTile();
	District* getDistrict();
	void takeAction();
	string getName();
};

#endif /* CITIZEN_H_ */
