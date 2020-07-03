#include "Tile.h"

#include <stdexcept>

Tile::Tile(short x, short y, TileProperty::TileProperty property) : coordinates(TileCoordinates(x, y)), pEntity(nullptr), property(property) {
	updateColour();
}

Tile::~Tile() {}

TileCoordinates Tile::getCoordinates() const {
	return coordinates;
}

int Tile::getX() const {
	return coordinates.x;
}

int Tile::getY() const {
	return coordinates.y;
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
