#include "Citizen.h"

Citizen::Citizen(string name) : tile(nullptr), citizenName(name) {

}

Citizen::Citizen() : Citizen("unnamed") {

}

Citizen::~Citizen() {

}

/*
 * Called by Tile::enterCitizen() after the citizen successfully moves to a different tile
 */
void Citizen::setTile(Tile* tile) {
	this->tile = tile;
}

Tile* Citizen::getTile() {
	return tile;
}

District* Citizen::getDistrict() {
	return tile->getDistrict();
}

/*
 * Called once per game tick.
 * This prompts the citizen to do something in the world (even if it's just moving about randomly).
 */
void Citizen::takeAction() {
	Tile* moveToTile = getDistrict()->getTile(tile->getX(), tile->getY() + 1);

	if (moveToTile != nullptr) {
		tile->citizenLeave();
		moveToTile->citizenEnter(this);
	}
}

string Citizen::getName() {
	return citizenName;
}
