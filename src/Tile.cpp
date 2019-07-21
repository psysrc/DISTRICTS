#include "Tile.h"

Tile::Tile() : Tile(-1, -1) {

}

Tile::Tile(int x, int y) : xCoord(x), yCoord(y) {
	occupyingCitizen = nullptr;
}

Tile::~Tile() {

}

/*
 * Sets the coordinates of this tile.
 * This should only ever be used immediately after the tile's creation!
 */
void Tile::setCoordinates(int x, int y) {
	xCoord = x;
	yCoord = y;
}

/*
 * Draws this tile.
 */
string Tile::draw() {
	return "#";
}
