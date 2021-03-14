#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "Entity.h"
#include "game/TileCoordinates.h"

class Citizen : public Entity {
public:
	Citizen(TileCoordinates = TileCoordinates(-1, -1));
	Citizen(const std::string&, TileCoordinates = TileCoordinates(-1, -1));
	virtual ~Citizen();
};

#endif /* CITIZEN_H_ */
