#include "PathTile.h"

PathTile::PathTile(Tile* tile, int distRemaining) : tile(tile), pathLength(0), distRemaining(distRemaining) {

}

PathTile::~PathTile() {

}

Tile* PathTile::getTile() const {
	return tile;
}

int PathTile::getDistRemaining() const {
	return distRemaining;
}

void PathTile::setPathLength(int length) {
	pathLength = length;
}

int PathTile::getPathLength() const {
	return pathLength;
}
