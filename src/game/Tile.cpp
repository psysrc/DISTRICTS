#include "Tile.h"

#include "game/District.h"
#include <stdexcept>
#include "entities/Citizen.h"

Tile::Tile(short x, short y) : coordinates(TileCoordinates(x, y)), pEntity(nullptr), property(TileProperty::NullProperty), drawColour(COLOUR_UNKNOWN) {}

Tile::~Tile() {}

TileCoordinates Tile::getCoordinates() const {
	return coordinates;
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
	return (District::validTileIndex(coordinates.x) && District::validTileIndex(coordinates.y) && property != TileProperty::NullProperty);
}

int Tile::getX() const {
	return coordinates.x;
}

int Tile::getY() const {
	return coordinates.y;
}

/*
 * Returns the neighbouring tile in the given direction.
 */
Tile* Tile::getNeighbourTile(int direction) const {
	return neighbourTiles[direction];
}

void Tile::updateProperty(TileProperty::TileProperty newProperty) {
	property = newProperty;

	updateColour();
}

TileProperty::TileProperty Tile::getProperty() const {
	return property;
}

Entity* Tile::getEntity() const {
	return pEntity;
}

/*
 * The given entity will occupy this Tile unless the tile is already occupied.
 */
bool Tile::occupy(Entity* pEntity) {
	if (getEntity() != nullptr)
		return false;

	this->pEntity = pEntity;

	return true;
}

/*
 * Calling this tells the Tile it is no longer occupied by an entity, if it had one.
 * Returns a pointer to the vacated entity, or nullptr if there was none.
 */
Entity* Tile::vacateEntity() {
	if (getEntity() != nullptr) {
		Entity* tmp = pEntity;
		pEntity = nullptr;

		return tmp;
	}

	return nullptr;
}

/*
 * Updates the tile colour.
 * Should be called whenever the tile's properties/characteristics change.
 */
void Tile::updateColour() {
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
