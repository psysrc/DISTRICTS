#ifndef SRC_TREE_H_
#define SRC_TREE_H_

#include "entities/Entity.hpp"
#include "game/TileCoordinates.hpp"

std::unique_ptr<Entity> makeTree(TileCoordinates);

#endif /* SRC_TREE_H_ */
