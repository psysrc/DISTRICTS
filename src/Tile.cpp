#include "Tile.h"

Tile::Tile() : pDistrict(nullptr), xCoord(-1), yCoord(-1), property(NullProperty), pOccupyingCitizen(nullptr) {

}

Tile::~Tile() {

}

/*
 * Tells the tile which district it is contained within.
 * This should only ever be used immediately after the tile's creation!
 */
void Tile::setDistrict(District* dist) {
	pDistrict = dist;
}

District* Tile::getDistrict() {
	return pDistrict;
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
 * Checks whether or not this Tile has been initialised with valid data.
 * The Tile object must not be used if it has not been initialised correctly!
 */
bool Tile::isInitialised() {
	return !(pDistrict == nullptr || xCoord == -1 || yCoord == -1);
}

int Tile::getX() {
	return xCoord;
}

int Tile::getY() {
	return yCoord;
}

void Tile::updateProperty(TileProperty newProperty) {
	property = newProperty;
}

TileProperty Tile::getProperty() {
	return property;
}

/*
 * Calling this tells the tile that the supplied Citizen is now occupying this tile.
 * This also informs the supplied Citizen of the tile change via Citizen::setTile().
 * This is assuming the tile is not already occupied.
 */
void Tile::citizenEnter(Citizen* citizen) {
	if (pOccupyingCitizen == nullptr) {
		pOccupyingCitizen = citizen;

		pOccupyingCitizen->setTile(this);
	}
}

/*
 * Calling this vacates the tile of its citizen (if it has one) and returns the Citizen*.
 * This also informs the supplied citizen of the tile change via Citizen::setTile().
 */
Citizen* Tile::citizenLeave() {
	if (pOccupyingCitizen != nullptr) {
		pOccupyingCitizen->setTile(nullptr);

		Citizen* temp = pOccupyingCitizen;
		pOccupyingCitizen = nullptr;
		return temp;
	}

	return nullptr;
}

/*
 * Draws this tile depending on its properties.
 */
chtype Tile::draw() {
	if (pOccupyingCitizen != nullptr)
		return 'C';

	switch (property) {
	case Plains:
		return ',';
	case Stone:
		return '%';
	case Water:
		return '~';
	case Tree:
		return '@';
	default:
		return '?';
	}
}
