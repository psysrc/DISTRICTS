#ifndef TILE_H_
#define TILE_H_

#include "game/TileCoordinates.h"
#include <vector>
#include "tasks/Task.h"

class District;
class Entity;

class DeprecatedTile
{
public:
	DeprecatedTile(TileCoordinates);
	~DeprecatedTile();
	TileCoordinates getCoordinates() const;
	Entity *getEntity() const;
	void setEntity(Entity *);
	const std::vector<Tasks::Task *> &getTasks() const;
	template <class T>
	bool hasTask() const;
	void addTask(Tasks::Task *);
	void removeTask(Tasks::Task *);
	bool operator==(const DeprecatedTile &b) const;

private:
	TileCoordinates coordinates;
	Entity *pEntity;
	int drawColour;
	std::vector<Tasks::Task *> tasks;
};

/**
 * Returns whether or not this tile currently has a task of the given type.
 */
template <class T>
bool DeprecatedTile::hasTask() const
{
	static_assert(std::is_base_of<Tasks::Task, T>::value, "T must extend Task");

	bool taskTypeExists = false;

	// Check all existing tasks on this tile
	for (Tasks::Task *pExistingTask : getTasks())
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
