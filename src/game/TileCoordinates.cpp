#include "game/TileCoordinates.hpp"

TileCoordinates::TileCoordinates(short x, short y) : x(x), y(y) {}

TileCoordinates::~TileCoordinates() {}

bool TileCoordinates::operator==(const TileCoordinates &b) const
{
	return (x == b.x) && (y == b.y);
}

bool TileCoordinates::operator!=(const TileCoordinates &b) const
{
	return !(*this == b);
}

bool TileCoordinates::operator<(const TileCoordinates &b) const
{
	return (x < b.x) || ((x == b.x) && (y < b.y));
}
