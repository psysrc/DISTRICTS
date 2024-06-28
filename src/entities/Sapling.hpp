#ifndef SRC_SAPLING_H_
#define SRC_SAPLING_H_

#include "entities/Entity.hpp"
#include "game/TileCoordinates.hpp"

std::unique_ptr<Entity> makeSapling(TileCoordinates coords);

#endif /* SRC_SAPLING_H_ */
