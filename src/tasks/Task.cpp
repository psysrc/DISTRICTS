#include "Task.h"

using namespace Tasks;

Task::Task(Tile* pTile, std::string taskName, int work)
: id(uniqueTaskID()), pTile(pTile), name(taskName), completed(false), workRemaining(work) {

}

Task::~Task() {}

ID_t Task::getID() const {
	return id;
}

Tile* Task::getTile() const {
	return pTile;
}

std::string Task::getName() const {
	return name;
}

bool Task::isCompleted() const { 
	return completed;
}

int Task::getWorkRemaining() const {
	return workRemaining;
}

/**
 * Perform one unit of work on this task.
 * Calling this when the task is already completed is a no-op.
 */
void Task::workOn() {
	if (completed)
		return;

	workRemaining--;

	if (workRemaining <= 0) {
		completed = true;
		onCompletion();
	}
}
