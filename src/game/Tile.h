#ifndef TILE_H_
#define TILE_H_

#include "game/TileCoordinates.h"
#include <vector>

class DeprecatedTile
{
public:
	DeprecatedTile(TileCoordinates);
	~DeprecatedTile();
	TileCoordinates getCoordinates() const;
	bool operator==(const DeprecatedTile &b) const;

private:
	TileCoordinates coordinates;
};

#endif /* TILE_H_ */
