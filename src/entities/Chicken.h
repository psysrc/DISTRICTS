#ifndef CHICKEN_H_
#define CHICKEN_H_

#include "entities/Entity.h"
#include "game/TileCoordinates.h"

std::unique_ptr<Entity> makeChicken(TileCoordinates coords);

#endif /* CHICKEN_H_ */
