#ifndef CITIZEN_H_
#define CITIZEN_H_

class Citizen;

#include <string>
#include "Tile.h"
#include "Constants.h"
#include "Entity.h"

class Citizen : public Entity {
public:
	Citizen(const std::string name);
	virtual ~Citizen();
	virtual void simulate() override;
	void move(MoveDirection direction);
	void move(Tile* const moveToTile);
};

#endif /* CITIZEN_H_ */
