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

void Tile::citizenEnter(Citizen* citizen) {
	if (occupyingCitizen == nullptr)
		occupyingCitizen = citizen;
}

Citizen* Tile::citizenLeave() {
	if (occupyingCitizen != nullptr) {
		Citizen* temp = occupyingCitizen;
		occupyingCitizen = nullptr;
		return temp;
	}

	return nullptr;
}

/*
 * Draws this tile depending on its properties.
 */
string Tile::draw() {
	if (occupyingCitizen == nullptr)
		return "#";
	else
		return "C";
}
