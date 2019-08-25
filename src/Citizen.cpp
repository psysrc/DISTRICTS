#include "Citizen.h"

Citizen::Citizen(std::string name) : Entity(name, 'C'), pTile(nullptr) {

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
void Citizen::simulate() {
	// The citizen will try to move in a random direction
	switch (rand() % 4) {
		case 0:
			move(North);
			break;
		case 1:
			move(West);
			break;
		case 2:
			move(East);
			break;
		case 3:
			move(South);
			break;
		default:
			throw 0;
	}
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
	if (moveToTile != nullptr) {				// If the other tile is valid
		if (moveToTile->citizenEnter(this)) {	// Attempt to move to the other tile
			// If successful, remember which tile we are now occupying and inform the old tile of the change
			pTile->vacateEntity();
			pTile = moveToTile;
		}
	}
}
