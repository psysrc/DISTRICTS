#include "Tile.h"

#include <stdexcept>

Tile::Tile(TileCoordinates coords, TileProperty::TileProperty property) : coordinates(coords), pEntity(nullptr), property(property) {
	updateColour();
}

Tile::~Tile() {}

TileCoordinates Tile::getCoordinates() const {
	return coordinates;
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

void Tile::setEntity(Entity* pEntity) {
	this->pEntity = pEntity;
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
	if (coordinates == b.getCoordinates())
		return true;
	else
		return false;
}
