#include "Tile.h"

Tile::Tile() : xCoord(-1), yCoord(-1) {

}

Tile::Tile(int x, int y) : xCoord(x), yCoord(y) {

}

Tile::~Tile() {

}

void Tile::setCoordinates(int x, int y) {
	xCoord = x;
	yCoord = y;
}
