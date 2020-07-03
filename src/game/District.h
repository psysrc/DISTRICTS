#ifndef DISTRICT_H_
#define DISTRICT_H_

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "game/Constants.h"
#include "entities/Entity.h"
#include "tasks/Task.h"
#include "game/Tile.h"
#include "ID.h"

class Citizen;

namespace Tasks {
class Task;
}

class District {
private:
	std::string districtName;
	std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
	std::vector<std::unique_ptr<Entity>> entities;			// All entities in the district
	std::vector<std::unique_ptr<Entity>> entitiesToAdd;		// All entities to add at the end of a game tick
	std::vector<Entity*> entitiesToDelete;					// All entities to delete at the end of a game tick
	std::vector<std::shared_ptr<Tasks::Task>> tasks;		// All tasks in the district
	std::vector<std::shared_ptr<Tasks::Task>> tasksToAdd;	// All tasks to add at the end of a game tick
	std::vector<Tasks::Task*> tasksToDelete;				// All tasks to delete at the end of a game tick
	std::map<TileCoordinates, ID_t> entityOccupyMap;		// Which entities occupy certain tiles
	std::map<TileCoordinates, ID_t> taskOccupyMap;			// Which tasks occupy certain tiles
public:
	static const unsigned short districtSize = 32;
	
	District(const std::string name = "unnamed");
	~District();
	std::string getName() const;
	static bool validTileIndex(const short);
	void createBiome(int i, int j, TileProperty::TileProperty biomeProperty, int size);
	void update();

	template <class E, typename... EArgs> E* makeEntity(EArgs...);
	Entity* getEntity(ID_t) const;
	const std::vector<std::unique_ptr<Entity>>& getEntities() const;
	void deleteEntity(Entity* entity);

	template <class T, typename... TArgs> T* makeTask(TArgs...);
	Tasks::Task* getTask(ID_t) const;
	std::shared_ptr<Tasks::Task> getLatestTask() const;
	std::shared_ptr<Tasks::Task> getOldestTask() const;
	void deleteTask(Tasks::Task* task);

	const std::vector<std::vector<std::unique_ptr<Tile>>>& getTiles() const;
	Tile* getTile(short, short) const;
	Tile* getTile(TileCoordinates) const;
	std::vector<Tile*> getNeighbourTiles(Tile*, bool = true) const;
};

/*
 * Creates a new Entity in the District on a given Tile, passing any arguments to the entity's constructor.
 * Returns a pointer to the newly created Entity.
 */
template <class E, typename... EArgs>
E* District::makeEntity(EArgs... args) {
	static_assert(std::is_base_of<Entity, E>::value, "E must extend Entity");

	std::unique_ptr<E> upE = std::make_unique<E>(args...);
	E* pE = upE.get();

	entitiesToAdd.push_back(std::move(upE));

	return pE;
}

/*
 * Creates a new Task in the District, passing any arguments to the task's constructor.
 * Returns a pointer to the newly created Task.
 */
template <class T, typename... TArgs>
T* District::makeTask(TArgs... args) {
	static_assert(std::is_base_of<Tasks::Task, T>::value, "T must extend Task");

	std::shared_ptr<T> upT = std::make_shared<T>(args...);
	T* pT = upT.get();

	tasksToAdd.push_back(std::move(upT));

	return pT;
}

#endif /* DISTRICT_H_ */
