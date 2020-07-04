#ifndef SRC_SAPLING_H_
#define SRC_SAPLING_H_

#include "Entity.h"
#include "game/Tile.h"

class Sapling : public Entity {
public:
	Sapling();
	Sapling(TileCoordinates);
	virtual ~Sapling();
};

#endif /* SRC_SAPLING_H_ */
