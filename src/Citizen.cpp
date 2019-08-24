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

Tile* Citizen::getTile() const {
	return pTile;
}

District* Citizen::getDistrict() const {
	return pTile->getDistrict();
}

/*
 * Called once per game tick.
 * This prompts the citizen to do something in the world (even if it's just moving about randomly).
 */
void Citizen::takeAction() {
	move(South);
}

/*
 * Moves the Citizen to a neighbouring tile.
 */
void Citizen::move(MoveDirection direction) {
	switch (direction) {
		case North:
			move(pTile->getNorthTile());
			break;
		case West:
			move(pTile->getWestTile());
			break;
		case East:
			move(pTile->getEastTile());
			break;
		case South:
			move(pTile->getSouthTile());
			break;
	}
}

/*
 * Moves the Citizen to another tile.
 * NOTE: There are currently no checks done to ensure the Citizen moves in a legal way
 * 		-> i.e. the Citizen shouldn't be able to jump all over the map
 */
void Citizen::move(Tile* const moveToTile) {
	if (moveToTile != nullptr) {		// If the other tile is valid
		pTile->citizenLeave();			// Leave the current tile
		moveToTile->citizenEnter(this);	// Enter the other tile
	}
}

string Citizen::getName() const {
	return citizenName;
}
