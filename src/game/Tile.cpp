#include "Tile.h"

#include "ui/TileColours.h"
#include <algorithm>

DeprecatedTile::DeprecatedTile(TileCoordinates coords) : coordinates(coords)
{

}

DeprecatedTile::~DeprecatedTile() {}

TileCoordinates DeprecatedTile::getCoordinates() const
{
	return coordinates;
}

bool DeprecatedTile::operator==(const DeprecatedTile &b) const
{
	return (coordinates == b.getCoordinates());
}
