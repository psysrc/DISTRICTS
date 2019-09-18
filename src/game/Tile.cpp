#include "Tile.h"

#include "game/District.h"
#include <stdexcept>
#include "entities/Entity.h"
#include "entities/Citizen.h"

Tile::Tile()
: pDistrict(nullptr), xCoord(-1), yCoord(-1), pEntity(nullptr),
  property(TileProperty::NullProperty), drawSymbol('?'), drawColour(COLOUR_UNKNOWN) {

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
	if (!District::validTileIndex(x) || !District::validTileIndex(y))
		throw std::length_error("Tile::setCoordinates(): Provided coordinates are not valid indexes");

	xCoord = x;
	yCoord = y;
}

/*
 * Sets the neighbouring tiles.
 */
void Tile::setNeighbourTiles(const std::vector<Tile*> neighbours) {
	if (neighbours.size() != 8)
		throw std::length_error("Tile::setNeighbourTiles(): Provided vector must contain exactly 8 elements");

	neighbourTiles.reserve(8);
	neighbourTiles = neighbours;
}

/*
 * Checks whether or not this Tile has been initialised with valid data.
 * The Tile object must not be used if it has not been initialised correctly!
 */
bool Tile::isInitialised() const {
	return !(pDistrict == nullptr || xCoord == -1 || yCoord == -1 || property == TileProperty::NullProperty);
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
Tile* Tile::getNeighbourTile(int direction) const {
	return neighbourTiles[direction];
}

void Tile::updateProperty(TileProperty::TileProperty newProperty) {
	property = newProperty;

	updateVisuals();
}

TileProperty::TileProperty Tile::getProperty() const {
	return property;
}

Entity* Tile::getEntity() const {
	return pEntity;
}

/*
 * Returns whether or not this tile is walkable.
 */
bool Tile::walkable() const {
	if (property == TileProperty::Water)
		return false;

	if (occupied())
		return false;

	return true;
}

/*
 * Identical to Tile::occupy(Entity*) but specialised for Citizens.
 * Checks, for example, if the citizen can walk on the tile (i.e. is it water?)
 */
bool Tile::citizenEnter(Citizen* pCitizen) {
	if (!walkable())
		return false;

	return occupy(pCitizen);	// The citizen will attempt to occupy the tile
}

/*
 * The given entity will occupy this Tile unless the tile is already occupied.
 */
bool Tile::occupy(Entity* pEntity) {
	if (occupied())
		return false;

	this->pEntity = pEntity;

	updateVisuals();

	return true;
}

/*
 * Calling this tells the Tile it is no longer occupied by an entity, if it had one.
 * Returns a pointer to the vacated entity, or nullptr if there was none.
 */
Entity* Tile::vacateEntity() {
	if (occupied()) {
		Entity* tmp = pEntity;
		pEntity = nullptr;
		updateVisuals();

		return tmp;
	}

	return nullptr;
}

/*
 * Returns whether or not the tile is occupied by another entity.
 */
bool Tile::occupied() const {
	return (pEntity != nullptr);
}

/*
 * Updates the symbol representation and colours for this Tile.
 * Should be called whenever the tile's properties/characteristics change.
 */
void Tile::updateVisuals() {
	if (pEntity != nullptr)
		drawSymbol = pEntity->getDrawSymbol();
	else
		drawSymbol = ' ';

	switch (property) {
	case TileProperty::Plains:
		drawColour = COLOUR_PLAINS;
		break;
	case TileProperty::Stone:
		drawColour = COLOUR_STONE;
		break;
	case TileProperty::Water:
		drawColour = COLOUR_WATER;
		break;
	case TileProperty::Bridge:
		drawColour = COLOUR_BRIDGE;
		break;
	default:
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
