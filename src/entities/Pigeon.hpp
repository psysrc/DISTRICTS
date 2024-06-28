#ifndef PIGEON_H_
#define PIGEON_H_

#include "entities/Entity.hpp"
#include "game/TileCoordinates.hpp"

std::unique_ptr<Entity> makePigeon(TileCoordinates coords);

#endif /* PIGEON_H_ */
