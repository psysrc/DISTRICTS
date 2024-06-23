#ifndef TILE_H_
#define TILE_H_

#include "game/TileCoordinates.h"
#include <vector>
#include "tasks/Task.h"

class DeprecatedTile
{
public:
	DeprecatedTile(TileCoordinates);
	~DeprecatedTile();
	TileCoordinates getCoordinates() const;
	const std::vector<Tasks::DeprecatedTask *> &getTasks() const;
	template <class T>
	bool hasTask() const;
	void addTask(Tasks::DeprecatedTask *);
	void removeTask(Tasks::DeprecatedTask *);
	bool operator==(const DeprecatedTile &b) const;

private:
	TileCoordinates coordinates;
	std::vector<Tasks::DeprecatedTask *> tasks;
};

/**
 * Returns whether or not this tile currently has a task of the given type.
 */
template <class T>
bool DeprecatedTile::hasTask() const
{
	static_assert(std::is_base_of<Tasks::DeprecatedTask, T>::value, "T must extend DeprecatedTask");

	bool taskTypeExists = false;

	// Check all existing tasks on this tile
	for (Tasks::DeprecatedTask *pExistingTask : getTasks())
	{
		// Check if a task of the given type already exists
		if (dynamic_cast<T *>(pExistingTask) != nullptr)
		{
			taskTypeExists = true;
			break;
		}
	}

	return taskTypeExists;
}

#endif /* TILE_H_ */
