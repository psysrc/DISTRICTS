#ifndef SRC_SAPLING_H_
#define SRC_SAPLING_H_

#include "entities/Entity.h"
#include "game/TileCoordinates.h"

std::unique_ptr<Entity> makeSapling(TileCoordinates coords);

#endif /* SRC_SAPLING_H_ */
