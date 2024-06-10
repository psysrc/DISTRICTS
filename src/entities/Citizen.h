#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "entities/Entity.h"
#include "game/TileCoordinates.h"

std::unique_ptr<Entity> makeCitizen(TileCoordinates coords);
std::unique_ptr<Entity> makeCitizen(TileCoordinates coords, const std::string& name);

#endif /* CITIZEN_H_ */
