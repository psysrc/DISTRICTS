#ifndef DUCK_H_
#define DUCK_H_

#include "entities/Entity.hpp"
#include "game/TileCoordinates.hpp"

std::unique_ptr<Entity> makeDuck(TileCoordinates coords);

#endif /* DUCK_H_ */
