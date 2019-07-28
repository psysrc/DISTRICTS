#include "Citizen.h"

Citizen::Citizen(string name) : pTile(nullptr), citizenName(name) {

}

Citizen::Citizen() : Citizen("unnamed") {

}

Citizen::~Citizen() {

}

/*
 * Called by Tile::enterCitizen() after the citizen successfully moves to a different tile
 */
void Citizen::setTile(Tile* tile) {
	pTile = tile;
}

Tile* Citizen::getTile() {
	return pTile;
}

District* Citizen::getDistrict() {
	return pTile->getDistrict();
}

/*
 * Called once per game tick.
 * This prompts the citizen to do something in the world (even if it's just moving about randomly).
 */
void Citizen::takeAction() {
	Tile* moveToTile = getDistrict()->getTile(pTile->getX(), pTile->getY() + 1);

	if (moveToTile != nullptr) {
		pTile->citizenLeave();
		moveToTile->citizenEnter(this);
	}
}

string Citizen::getName() {
	return citizenName;
}
