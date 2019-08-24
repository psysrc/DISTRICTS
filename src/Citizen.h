#ifndef CITIZEN_H_
#define CITIZEN_H_

class Citizen;

enum MoveDirection {
	North, West, East, South
};

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
	Tile* getTile() const;
	District* getDistrict() const;
	void takeAction();
	void move(MoveDirection direction);
	void move(Tile* const moveToTile);
	string getName() const;
};

#endif /* CITIZEN_H_ */
