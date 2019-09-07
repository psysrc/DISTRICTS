#include "Citizen.h"

Citizen::Citizen(District* district, std::string name) : Entity(district, name, 'C'), pCurrentTask(nullptr) {

}

Citizen::~Citizen() {

}

/*
 * Called once per game tick.
 * This prompts the citizen to do something in the world (even if it's just moving about randomly).
 */
void Citizen::simulate() {
//	if (upCurrentPath == nullptr)
//		upCurrentPath = PathFinding::findPath(pTile, pDistrict->getTile(rand() % DISTRICT_SIZE, rand() % DISTRICT_SIZE));
//	else {
//		Tile* nextTile = upCurrentPath->next();
//
//		if (nextTile != nullptr)
//			move(nextTile);
//		else
//			upCurrentPath = nullptr;
//	}

	if (pCurrentTask != nullptr && upCurrentPath.get() != nullptr) {	// Citizen has a task and knows how to get to it
		if (pCurrentTask->citizenInRange(this)) {
			pCurrentTask->workOn(this);

			if (pCurrentTask->isCompleted())
				pCurrentTask = nullptr;
		}
		else {
			move(upCurrentPath->next());	// Move towards the task (NOTE: No nullptr checks! Shouldn't be an issue though.)
		}
	}
	else {
		pCurrentTask = pDistrict->getLatestTask();
		upCurrentPath = PathFinding::findPath(pTile, pCurrentTask->getTile());

		if (upCurrentPath.get() == nullptr) {
			// Latest task cannot be reached
			UI::displayActivityMessage("I can't get to the latest task! Halp pls!");
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

