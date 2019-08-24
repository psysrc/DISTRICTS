#ifndef CITIZEN_H_
#define CITIZEN_H_

class Citizen;

#include <string>
#include "Tile.h"
#include "Constants.h"

class Citizen {
private:
	Tile* pTile;
	std::string citizenName;
public:
	Citizen(const std::string name);
	Citizen();
	~Citizen();
	void setTile(Tile* tile);
	Tile* getTile() const;
	District* getDistrict() const;
	void takeAction();
	void move(MoveDirection direction);
	void move(Tile* const moveToTile);
	std::string getName() const;
};

#endif /* CITIZEN_H_ */
