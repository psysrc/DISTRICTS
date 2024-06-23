#ifndef PIGEON_H_
#define PIGEON_H_

#include "entities/Entity.h"
#include "game/TileCoordinates.h"

std::unique_ptr<Entity> makePigeon(TileCoordinates coords);

#endif /* PIGEON_H_ */
