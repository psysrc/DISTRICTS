#ifndef DISTRICT_H_
#define DISTRICT_H_

#include <string>
#include <vector>
#include <memory>
#include "game/Constants.h"
#include "game/Tile.h"
#include "entities/Entity.h"

class Citizen;

namespace Tasks {
class Task;
}

class District {
private:
	std::string districtName;
	Tile** tiles;
	std::vector<std::unique_ptr<Entity>> entities;			// All entities in the district
	std::vector<std::unique_ptr<Entity>> entitiesToAdd;		// All entities to add at the end of a game tick
	std::vector<Entity*> entitiesToDelete;					// All entities to delete at the end of a game tick
	std::vector<std::shared_ptr<Tasks::Task>> tasks;		// All tasks in the district
	std::vector<std::shared_ptr<Tasks::Task>> tasksToAdd;	// All tasks to add at the end of a game tick
	std::vector<Tasks::Task*> tasksToDelete;				// All tasks to delete at the end of a game tick
public:
	District(const std::string name = "unnamed");
	~District();
	static bool validTileIndex(const int index);
	void createBiome(int i, int j, TileProperty::TileProperty biomeProperty, int size);
	void simulate();
	const std::vector<std::unique_ptr<Entity>>& getEntities() const;
	Tasks::Task* getLatestTask() const;
	Tasks::Task* getOldestTask() const;
	template <class E> E* makeEntity();
	template <class T> T* makeTask(Tile*);
	std::string getName() const;
	Tile** getTiles() const;
	Tile* getTile(const int i, const int j) const;
	void deleteEntity(Entity* entity);
	void deleteTask(Tasks::Task* task);
};

/*
 * Creates a new Entity in the District on a given Tile.
 * Returns a pointer to the newly created Entity, or nullptr if the entity could not be created.
 */
template <class E>
E* District::makeEntity() {
	static_assert(std::is_base_of<Entity, E>::value, "E must extend Entity");

	std::unique_ptr<E> upE = std::make_unique<E>();
	E* pE = upE.get();

	entitiesToAdd.push_back(std::move(upE));

	return pE;
}

/*
 * Creates a new Task in the District.
 * Returns a pointer to the newly created Task.
 */
template <class T>
T* District::makeTask(Tile* tile) {
	static_assert(std::is_base_of<Tasks::Task, T>::value, "T must extend Task");

	std::shared_ptr<T> upT = std::make_shared<T>(this, tile);
	T* pT = upT.get();

	tasksToAdd.push_back(std::move(upT));

	return pT;
}

#endif /* DISTRICT_H_ */
