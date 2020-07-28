#include "Tile.h"

#include "ui/TileColours.h"
#include <algorithm>

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

const std::vector<Tasks::Task*>& Tile::getTasks() const {
	return tasks;
}

void Tile::addTask(Tasks::Task* pTask) {
	tasks.push_back(pTask);
}

void Tile::removeTask(Tasks::Task* pTask) {
	tasks.erase(std::find(tasks.begin(), tasks.end(), pTask));
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
	return (coordinates == b.getCoordinates());
}
