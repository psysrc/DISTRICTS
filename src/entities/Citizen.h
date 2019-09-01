#ifndef CITIZEN_H_
#define CITIZEN_H_

class Citizen;

#include "pathfinding/Path.h"
#include "pathfinding/PathFinding.h"
#include <string>
#include "game/Tile.h"
#include "game/Constants.h"
#include "Entity.h"

class Citizen : public Entity {
private:
	std::unique_ptr<Path> upCurrentPath;
public:
	Citizen(District*, const std::string);
	virtual ~Citizen();
	virtual void simulate() override;
	void move(int direction);
	void move(Tile* const moveToTile);
};

#endif /* CITIZEN_H_ */
