#include "Citizen.h"

Citizen::Citizen(std::string name) : pTile(nullptr), citizenName(name) {

}

Citizen::Citizen() : Citizen("unnamed") {

}

Citizen::~Citizen() {

}

/*
 * Sets the current tile the Citizen is on.
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
	move(East);
}

/*
 * Attempts to move the Citizen to a neighbouring tile in a given direction.
 */
void Citizen::move(MoveDirection direction) {
	move(pTile->getNeighbourTile(direction));
}

/*
 * Attempts to move the Citizen to another tile.
 * NOTE: There are currently no checks done to ensure the Citizen moves in a legal way
 * 		-> i.e. the Citizen shouldn't be able to jump all over the map
 */
void Citizen::move(Tile* const moveToTile) {
	if (moveToTile != nullptr)					// If the other tile is valid
		if (moveToTile->citizenEnter(this))		// Attempt to move to the other tile
			pTile = moveToTile;					// If successful, remember which tile we are now occupying
}

std::string Citizen::getName() const {
	return citizenName;
}
