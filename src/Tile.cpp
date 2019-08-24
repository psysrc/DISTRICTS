#include "Tile.h"

Tile::Tile()
: pDistrict(nullptr), xCoord(-1), yCoord(-1), occupiedByCitizen(false), property(NullProperty), drawSymbol('?'), drawColour(COLOUR_UNKNOWN) {

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

District* Tile::getDistrict() const {
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
 * Sets the neighbouring tiles.
 */
void Tile::setNeighbourTiles(Tile* const n, Tile* const w, Tile* const e, Tile* const s) {
	northTile = n;
	westTile = w;
	eastTile = e;
	southTile = s;
}

/*
 * Checks whether or not this Tile has been initialised with valid data.
 * The Tile object must not be used if it has not been initialised correctly!
 */
bool Tile::isInitialised() const {
	return !(pDistrict == nullptr || xCoord == -1 || yCoord == -1 || property == NullProperty);
}

int Tile::getX() const {
	return xCoord;
}

int Tile::getY() const {
	return yCoord;
}

/*
 * Returns the neighbouring tile in the given direction.
 */
Tile* const Tile::getNeighbourTile(MoveDirection direction) const {
	switch (direction) {
		case North:
			return northTile;
		case West:
			return westTile;
		case East:
			return eastTile;
		case South:
			return southTile;
		default:
			return nullptr;
	}
}

void Tile::updateProperty(TileProperty newProperty) {
	property = newProperty;

	updateVisuals();
}

TileProperty Tile::getProperty() const {
	return property;
}

/*
 * Calling this method effectively asks the tile if a Citizen can enter it.
 * Returns whether or not the Citizen is now occupying this Tile.
 */
bool Tile::citizenEnter() {
	if (property == Water)		// Can Citizens walk on this tile?
		return false;

	if (occupiedByCitizen)		// Is this tile already occupied?
		return false;


	occupiedByCitizen = true;

	updateVisuals();

	return true;
}

/*
 * Calling this tells the Tile it is no longer occupied by a Citizen, if it has one.
 */
void Tile::citizenLeave() {
	if (occupiedByCitizen) {
		occupiedByCitizen = false;
		updateVisuals();
	}
}

/*
 * Updates the symbol representation and colours for this Tile.
 * Should be called whenever the tile's properties/characteristics change.
 */
void Tile::updateVisuals() {
	if (occupiedByCitizen) {
		drawSymbol = 'C';
		drawColour = COLOUR_CITIZEN;

		return;
	}

	switch (property) {
	case Plains:
		drawSymbol = ' ';
		drawColour = COLOUR_PLAINS;
		break;
	case Stone:
		drawSymbol = '%';
		drawColour = COLOUR_STONE;
		break;
	case Water:
		drawSymbol = '~';
		drawColour = COLOUR_WATER;
		break;
	case Tree:
		drawSymbol = '$';
		drawColour = COLOUR_PLAINS;
		break;
	default:
		drawSymbol = '?';
		drawColour = COLOUR_UNKNOWN;
		break;
	}
}

/*
 * Returns the draw symbol of this Tile.
 */
char Tile::getDrawSymbol() const {
	return drawSymbol;
}

/*
 * Returns the colour of this Tile.
 */
int Tile::getDrawColour() const {
	return drawColour;
}

bool Tile::operator==(const Tile& b) const {
	if (getX() == b.getX() && getY() == b.getY())
		return true;
	else
		return false;
}
