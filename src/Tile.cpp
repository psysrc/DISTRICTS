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
 * Calling this method effectively asks the tile if the Citizen can enter it.
 * If so, the Citizen then moves to this tile. If not, nothing happens.
 * The return value is the success of whether or not the Citizen has moved to this tile.
 * This method informs the Citizen's old tile through Tile::citizenLeave().
 */
bool Tile::citizenEnter(Citizen* citizen) {
	if (property == Water)				// Can Citizens walk on this tile?
		return false;

	if (pOccupyingCitizen != nullptr)	// Is this tile already occupied?
		return false;


	pOccupyingCitizen = citizen;

	Tile* const pPrevTile = citizen->getTile();

	if (pPrevTile != nullptr)		// If the Citizen has come from another tile (quite likely)
		pPrevTile->citizenLeave();	// Inform the Citizen's old tile that it has now left

	updateVisuals();

	return true;
}

/*
 * Calling this vacates the tile of its citizen (if it has one) and returns the Citizen*.
 */
Citizen* Tile::citizenLeave() {
	if (pOccupyingCitizen != nullptr) {
		Citizen* temp = pOccupyingCitizen;
		pOccupyingCitizen = nullptr;

		updateVisuals();

		return temp;
	}

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
