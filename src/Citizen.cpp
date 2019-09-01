#include "Citizen.h"

Citizen::Citizen(District* district, std::string name) : Entity(district, name, 'C'), pCurrentPath(nullptr) {

}

Citizen::~Citizen() {
	delete pCurrentPath;
}

/*
 * Called once per game tick.
 * This prompts the citizen to do something in the world (even if it's just moving about randomly).
 */
void Citizen::simulate() {
	if (pCurrentPath == nullptr)
		pCurrentPath = PathFinding::findPath(pTile, pDistrict->getTile(rand() % DISTRICT_SIZE, rand() % DISTRICT_SIZE));
	else {
		Tile* nextTile = pCurrentPath->next();

		if (nextTile != nullptr)
			move(nextTile);
		else {
			delete pCurrentPath;
			pCurrentPath = nullptr;
		}
	}
}

/*
 * Attempts to move the Citizen to a neighbouring tile in a given direction.
 */
void Citizen::move(int direction) {
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

/*
 * Tells the citizen to find a path to the given tile and start moving towards it.
 */
void Citizen::pathTo(Tile* goTo) {
	// TODO
	// Find a path to the tile
	// If one cannot be found, grumble
}

