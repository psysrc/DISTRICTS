#include "Task.h"

#include "game/Tile.h"

using namespace Tasks;

DeprecatedTask::DeprecatedTask(DeprecatedTile *pTile, std::string taskName, int work)
	: id(uniqueDeprecatedTaskID()), pTile(pTile), name(taskName), completed(false), workRemaining(work)
{
	pTile->addTask(this);
}

DeprecatedTask::~DeprecatedTask()
{
	pTile->removeTask(this);
}

ID_t DeprecatedTask::getID() const
{
	return id;
}

DeprecatedTile *DeprecatedTask::getTile() const
{
	return pTile;
}

std::string DeprecatedTask::getName() const
{
	return name;
}

bool DeprecatedTask::isCompleted() const
{
	return completed;
}

int DeprecatedTask::getWorkRemaining() const
{
	return workRemaining;
}

/**
 * Perform one unit of work on this task.
 * Calling this when the task is already completed is a no-op.
 */
void DeprecatedTask::workOn(District *pDistrict)
{
	if (completed)
		return;

	workRemaining--;

	if (workRemaining <= 0)
	{
		completed = true;
		onCompletion(pDistrict);
	}
}
