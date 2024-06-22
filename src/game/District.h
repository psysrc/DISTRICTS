#ifndef DISTRICT_H_
#define DISTRICT_H_

#include <string>
#include <vector>
#include <memory>
#include "entities/Entity.h"
#include "tasks/Task.h"
#include "game/Tile.h"
#include "ID.h"
#include "game/TileProperty.h"
#include <unordered_map>
#include "game/PositionLookup.h"

namespace Tasks
{
	class Task;
}

class District
{
public:
	static const unsigned short districtSize = 32;

	District();
	District(const std::string &name);
	~District();
	std::string getName() const;
	void createBiome(TileCoordinates, TileProperty::TileProperty biomeProperty, int size, std::unordered_map<TileCoordinates, TileProperty::TileProperty>& tile_map);
	void update();

	template <class E, typename... EArgs>
	E *makeEntity(EArgs...);
	void addEntity(std::unique_ptr<Entity> entity);
	Entity *getEntity(ID_t) const;
	const std::vector<std::unique_ptr<Entity>> &getEntities() const;
	void deleteEntity(Entity *entity);

	template <class T, typename... TArgs>
	T *makeTask(TArgs...);
	Tasks::Task *getTask(ID_t) const;
	std::shared_ptr<Tasks::Task> getLatestTask() const;
	std::shared_ptr<Tasks::Task> getOldestTask() const;
	void deleteTask(Tasks::Task *task);

	static bool validTileCoordinates(TileCoordinates);
	const std::vector<std::vector<std::unique_ptr<DeprecatedTile>>> &getTiles() const;
	DeprecatedTile *getTile(short, short) const;
	DeprecatedTile *getTile(TileCoordinates) const;
	std::vector<DeprecatedTile *> getNeighbourTiles(DeprecatedTile *, bool = true) const;
	std::vector<TileCoordinates> getNeighbourCoordinates(TileCoordinates, bool = true) const;

	const std::unordered_set<Entity*>& entitiesAtPosition(TileCoordinates);

private:
	std::string districtName;
	PositionLookup positionLookup;
	std::vector<std::vector<std::unique_ptr<DeprecatedTile>>> tiles;
	std::vector<std::unique_ptr<Entity>> entities;		  // All entities in the district
	std::vector<std::unique_ptr<Entity>> entitiesToAdd;	  // All entities to add at the end of a game tick
	std::vector<Entity *> entitiesToDelete;				  // All entities to delete at the end of a game tick
	std::vector<std::shared_ptr<Tasks::Task>> tasks;	  // All tasks in the district
	std::vector<std::shared_ptr<Tasks::Task>> tasksToAdd; // All tasks to add at the end of a game tick
	std::vector<Tasks::Task *> tasksToDelete;			  // All tasks to delete at the end of a game tick
};

/*
 * Creates a new Entity in the District on a given Tile, passing any arguments to the entity's constructor.
 * Returns a pointer to the newly created Entity.
 */
template <class E, typename... EArgs>
E *District::makeEntity(EArgs... args)
{
	static_assert(std::is_base_of<Entity, E>::value, "E must extend Entity");

	std::unique_ptr<E> upE = std::make_unique<E>(args...);
	E *pE = upE.get();

	entitiesToAdd.push_back(std::move(upE));

	return pE;
}

/*
 * Creates a new Task in the District, passing any arguments to the task's constructor.
 * Returns a pointer to the newly created Task.
 */
template <class T, typename... TArgs>
T *District::makeTask(TArgs... args)
{
	static_assert(std::is_base_of<Tasks::Task, T>::value, "T must extend Task");

	std::shared_ptr<T> upT = std::make_shared<T>(args...);
	T *pT = upT.get();

	tasksToAdd.push_back(std::move(upT));

	return pT;
}

#endif /* DISTRICT_H_ */
