#ifndef TILE_H_
#define TILE_H_

#include "game/TileCoordinates.h"
#include "game/TileProperty.h"
#include <vector>
#include "tasks/Task.h"

class District;
class Entity;

class Tile
{
public:
	Tile(TileCoordinates, TileProperty::TileProperty);
	~Tile();
	TileCoordinates getCoordinates() const;
	void updateProperty(TileProperty::TileProperty newProperty);
	TileProperty::TileProperty getProperty() const;
	Entity *getEntity() const;
	void setEntity(Entity *);
	const std::vector<Tasks::Task *> &getTasks() const;
	template <class T>
	bool hasTask() const;
	void addTask(Tasks::Task *);
	void removeTask(Tasks::Task *);
	int getDrawColour() const;
	bool operator==(const Tile &b) const;

private:
	TileCoordinates coordinates;
	Entity *pEntity;
	TileProperty::TileProperty property;
	int drawColour;
	std::vector<Tasks::Task *> tasks;
	void updateColour();
};

/**
 * Returns whether or not this tile currently has a task of the given type.
 */
template <class T>
bool Tile::hasTask() const
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
