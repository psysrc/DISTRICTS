#ifndef DISTRICT_H_
#define DISTRICT_H_

#include <string>
#include <vector>
#include <memory>
#include "game/Constants.h"

class Tile;
class Citizen;
class Entity;
class Task;

class District {
private:
	std::string districtName;
	Tile** tiles;
	std::vector<std::unique_ptr<Citizen>> citizens;			// All citizens in the district
	std::vector<std::unique_ptr<Entity>> entities;			// All entities in the district (not including citizens)
	std::vector<std::unique_ptr<Entity>> entitiesToAdd;		// All entities to add at the end of a game tick (not including citizens)
	std::vector<std::unique_ptr<Task>> tasks;				// All tasks in the district
	std::vector<std::unique_ptr<Task>> tasksToAdd;			// All tasks to add at the end of a game tick
public:
	District(const std::string name = "unnamed");
	~District();
	static bool validTileIndex(const int index);
	void createBiome(int i, int j, TileProperty biomeProperty, int size);
	void simulate();
	Task* getLatestTask() const;
	Task* getOldestTask() const;
	template <class E> E* makeEntity();
	template <class T> T* makeTask(Tile*);
	std::string getName() const;
	Tile** getTiles() const;
	Tile* getTile(const int i, const int j) const;
};

/*
 * Creates a new Entity in the District.
 * Returns a pointer to the newly created Entity.
 */
template <class E>
E* District::makeEntity() {
	static_assert(std::is_base_of<Entity, E>::value, "E must extend Entity");

	std::unique_ptr<E> upE = std::make_unique<E>(this);
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
	static_assert(std::is_base_of<Task, T>::value, "T must extend Task");

	std::unique_ptr<T> upT = std::make_unique<T>(this, tile);
	T* pT = upT.get();

	tasksToAdd.push_back(std::move(upT));

	return pT;
}

#endif /* DISTRICT_H_ */
