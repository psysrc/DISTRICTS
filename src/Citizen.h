#ifndef CITIZEN_H_
#define CITIZEN_H_

class Citizen;

#include <string>
#include "Tile.h"
#include "Constants.h"

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
	Tile* getTile() const;
	District* getDistrict() const;
	void takeAction();
	void move(MoveDirection direction);
	void move(Tile* const moveToTile);
	string getName() const;
};

#endif /* CITIZEN_H_ */
