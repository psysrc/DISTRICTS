#include "Task.h"

#include "entities/Citizen.h"
#include "pathfinding/PathFinding.h"
#include "game/District.h"
#include "components/PositionComponent.h"

using namespace Tasks;

Task::Task(District* district, Tile* tile, std::string taskName, int work)
: pTile(tile), name(taskName), completed(false), workRemaining(work), pDistrict(district) {

}

Task::~Task() {

}

/*
 * Returns whether or not the given Citizen is in range of this Task.
 */
bool Task::citizenInRange(Citizen* pCitizen) {
	// Citizen is considered to be in range when within 1.5 units of the task
	// This allows it to be on the task tile itself or any neighbour, but no further
	return (PathFinding::euclideanDistance(pCitizen->getComponent<PositionComponent>()->getTile(), pTile) < 1.5);
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
	}
}
