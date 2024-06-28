#ifndef DISTRICT_H_
#define DISTRICT_H_

#include <string>
#include <vector>
#include <memory>
#include "entities/Entity.hpp"
#include "game/TileCoordinates.hpp"
#include "ID.hpp"
#include "game/TileProperty.hpp"
#include <unordered_map>
#include "game/PositionLookup.hpp"
#include "game/TaskLookup.hpp"

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
	Entity* getEntity(ID_t) const;
	const std::vector<std::unique_ptr<Entity>> &getEntities() const;
	void deleteEntity(Entity *entity);

	static bool validTileCoordinates(TileCoordinates);
	std::vector<TileCoordinates> getNeighbourCoordinates(TileCoordinates, bool = true) const;

	const std::unordered_set<Entity*>& getEntitiesAtPosition(TileCoordinates);
	const std::vector<Entity*>& getTasks() const;

private:
	std::string districtName;
	std::vector<std::unique_ptr<Entity>> entities;		  // All entities in the district
	std::vector<std::unique_ptr<Entity>> entitiesToAdd;	  // All entities to add at the end of a game tick
	std::vector<Entity *> entitiesToDelete;				  // All entities to delete at the end of a game tick

	PositionLookup positionLookup;
	TaskLookup taskLookup;
};

#endif /* DISTRICT_H_ */
