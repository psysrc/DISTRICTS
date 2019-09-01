#ifndef CITIZEN_H_
#define CITIZEN_H_

class Citizen;

#include <string>
#include "Tile.h"
#include "Constants.h"
#include "Entity.h"
#include "PathFinding.h"

class Citizen : public Entity {
private:
	Path* currentPath;
public:
	Citizen(District*, const std::string);
	virtual ~Citizen();
	virtual void simulate() override;
	void move(int direction);
	void move(Tile* const moveToTile);
	void pathTo(Tile*);
};

#endif /* CITIZEN_H_ */
