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

	void addEntity(std::unique_ptr<Entity> entity);
	const std::vector<std::unique_ptr<Entity>> &getEntities() const;
	void deleteEntity(Entity *entity);

	void addTask(std::shared_ptr<Tasks::Task> task);
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

#endif /* DISTRICT_H_ */
