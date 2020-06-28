#include "Task.h"

using namespace Tasks;

Task::Task(Tile* tile, std::string taskName, int work)
: id(uniqueTaskID()), pTile(tile), name(taskName), completed(false), workRemaining(work) {

}

Task::~Task() {}

ID_t Task::getID() const {
	return id;
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
