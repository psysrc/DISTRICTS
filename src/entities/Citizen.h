#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "Entity.h"
#include "game/TileCoordinates.h"

class Citizen : public Entity {
public:
	Citizen();
	Citizen(TileCoordinates);
	virtual ~Citizen();
};

#endif /* CITIZEN_H_ */
