#ifndef SRC_TREE_H_
#define SRC_TREE_H_

#include "Entity.h"
#include "game/Tile.h"

class Tree : public Entity {
public:
	Tree();
	Tree(TileCoordinates);
	virtual ~Tree();
};

#endif /* SRC_TREE_H_ */
