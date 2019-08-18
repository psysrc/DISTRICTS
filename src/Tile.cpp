#include "Tile.h"

Tile::Tile()
: pDistrict(nullptr), xCoord(-1), yCoord(-1), property(NullProperty), pOccupyingCitizen(nullptr), drawSymbol('?'), drawColour(COLOUR_UNKNOWN) {

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

void Tile::updateProperty(TileProperty newProperty) {
	property = newProperty;

	updateVisuals();
}

TileProperty Tile::getProperty() const {
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

	updateVisuals();
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

		updateVisuals();

		return temp;
	}

	updateVisuals();

	return nullptr;
}

/*
 * Updates the symbol representation and colours for this Tile.
 * Should be called whenever the tile's properties/characteristics change.
 */
void Tile::updateVisuals() {
	if (pOccupyingCitizen != nullptr) {
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
chtype Tile::getDrawSymbol() const {
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
