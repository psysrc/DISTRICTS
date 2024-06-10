#ifndef SRC_TREE_H_
#define SRC_TREE_H_

#include "entities/Entity.h"
#include "game/TileCoordinates.h"

std::unique_ptr<Entity> makeTree(TileCoordinates);

#endif /* SRC_TREE_H_ */
