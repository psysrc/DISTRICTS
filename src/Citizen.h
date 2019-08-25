#ifndef CITIZEN_H_
#define CITIZEN_H_

class Citizen;

#include <string>
#include "Tile.h"
#include "Constants.h"
#include "Entity.h"

class Citizen : public Entity {
private:
	Tile* pTile;
public:
	Citizen(const std::string name);
	virtual ~Citizen();
	void setTile(Tile* tile);
	Tile* getTile() const;
	District* getDistrict() const;
	virtual void simulate() override;
	void move(MoveDirection direction);
	void move(Tile* const moveToTile);
};

#endif /* CITIZEN_H_ */
