#include "Tile.h"

Tile::Tile() : district(nullptr), xCoord(-1), yCoord(-1), occupyingCitizen(nullptr) {

}

Tile::~Tile() {

}

/*
 * Tells the tile which district it is contained within.
 * This should only ever be used immediately after the tile's creation!
 */
void Tile::setDistrict(District* dist) {
	district = dist;
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
 * Calling this tells the tile that the supplied Citizen is now occupying this tile.
 * This is assuming the tile is not already occupied.
 */
void Tile::citizenEnter(Citizen* citizen) {
	if (occupyingCitizen == nullptr)
		occupyingCitizen = citizen;
}

/*
 * Calling this vacates the tile of its citizen (if it has one).
 */
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
