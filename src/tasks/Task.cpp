#include "tasks/Task.h"
#include "entities/Citizen.h"

Task::Task(District* district, Tile* tile, std::string taskName, int work)
: deleteMe(false), pDistrict(district), pTile(tile), name(taskName), completed(false), workRemaining(work) {

}

Task::~Task() {

}

/*
 * Returns whether or not the given Citizen is in range of this Task.
 */
bool Task::citizenInRange(Citizen* pCitizen) {
	// Citizen is considered to be in range when within 1.5 units of the task
	// This allows it to be on the task tile itself or any neighbour, but no further
	return (PathFinding::euclideanDistance(pCitizen->getTile(), pTile) < 1.5);
}

/*
 * The given Citizen will work on this task assuming they are in range and the task is still incomplete.
 */
void Task::workOn(Citizen* pCitizen) {
	if (completed)
		return;

	if (!citizenInRange(pCitizen))
		return;

	workRemaining--;

	if (workRemaining <= 0) {
		completed = true;
		onCompletion();
		deleteTask();
	}
}
