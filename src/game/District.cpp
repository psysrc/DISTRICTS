#include "District.h"

#include "game/Tile.h"
#include "entities/Tree.h"
#include "entities/Sapling.h"
#include <algorithm>
#include "tasks/Task.h"
#include "entities/Citizen.h"
#include "components/PositionComponent.h"
#include "components/GrowComponent.h"
#include "entities/OccupyRules.h"
#include "helpers/DistrictNameGenerator.h"

#define BIOME_GEN true
#define TREE_GEN true

using namespace Tasks;

District::District() : District(DistrictNameGenerator::generateName()) {}

District::District(const std::string& name) : districtName(name)
{
	// Create the 2D array of Tiles
	tiles = std::vector<std::vector<std::unique_ptr<Tile>>>(District::districtSize);

	for (int x = 0; x < District::districtSize; x++)
		tiles[x] = std::vector<std::unique_ptr<Tile>>(District::districtSize);

	for (int y = 0; y < District::districtSize; y++) {
		for (int x = 0; x < District::districtSize; x++) {
			tiles[x][y] = std::make_unique<Tile>(TileCoordinates(x, y), TileProperty::Plains);
		}
	}

	if (BIOME_GEN) {
		// Generate biomes
		int stoneBiomes = rand() % 3 + 1;	// 1-3 stone biomes
		int lakeBiomes = rand() % 3 + 1;	// 1-3 lake biomes

		while (stoneBiomes--) {
			int ri = rand() % District::districtSize;
			int rj = rand() % District::districtSize;
			int size = rand() % 26 + 5;		// 5-30 tiles in size

			createBiome(TileCoordinates(ri, rj), TileProperty::Stone, size);
		}

		while (lakeBiomes--) {
			int ri = rand() % District::districtSize;
			int rj = rand() % District::districtSize;
			int size = rand() % 101 + 10;	// 10-100 tiles in size

			createBiome(TileCoordinates(ri, rj), TileProperty::Water, size);
		}
	}

	// Make a new citizen and place them on a walkable tile
	auto citizen = makeCitizen(TileCoordinates(-1, -1));

	int citizenX, citizenY;

	// Keep choosing random tiles until one is found in which the citizen can enter
	do {
		citizenX = rand() % District::districtSize;
		citizenY = rand() % District::districtSize;
	}
	while (!OccupyRules::canOccupy(citizen.get(), tiles[citizenX][citizenY].get()));

	citizen->getComponent<PositionComponent>()->nextCoordinates = tiles[citizenX][citizenY]->getCoordinates();
	addEntity(std::move(citizen));

	if (TREE_GEN) {
		// Every Plains tile has a chance to grow a Tree or Sapling, as long as the Citizen isn't already occupying it
		for (int i = 0; i < District::districtSize; i++) {
			for (int j = 0; j < District::districtSize; j++) {
				if (tiles[i][j]->getProperty() == TileProperty::Plains && !(i == citizenX && j == citizenY)) {
					int treeChance = rand() % 100;

					if (treeChance < 5) {	// 5% chance of growing a tree
						auto tree = makeTree(tiles[i][j]->getCoordinates());
						addEntity(std::move(tree));
					}
					else if (treeChance < 6) {	// 1% chance of growing a sapling
						auto sapling = makeSapling(tiles[i][j]->getCoordinates());
						addEntity(std::move(sapling));
					}
				}
			}
		}
	}
}

District::~District() {}

void District::addEntity(std::unique_ptr<Entity> entity) {
	entitiesToAdd.push_back(std::move(entity));
}

Entity* District::getEntity(ID_t /* entityID */) const {
	throw std::logic_error("District::getEntity() not yet implemented");
	return nullptr;
}

Tasks::Task* District::getTask(ID_t /* taskID */) const {
	throw std::logic_error("District::getTask() not yet implemented");
	return nullptr;
}

const std::vector<std::unique_ptr<Entity>>& District::getEntities() const {
	return entities;
}

/*
 * Returns whether or not a set of Tile coordinates is valid.
 */
bool District::validTileCoordinates(TileCoordinates coords) {
	return coords.x >= 0 && coords.x < districtSize && coords.y >= 0 && coords.y < districtSize;
}

/*
 * Creates/adds a new biome to the district at a given location, with a defined size
 */
void District::createBiome(TileCoordinates coords, TileProperty::TileProperty biomeProperty, int size) {
	if (!validTileCoordinates(coords))
		throw std::logic_error("District::createBiome - Invalid coordinates");

	std::vector<Tile*> adjacency;			// Contains tiles adjacent to converted tiles
	std::vector<Tile*>::iterator adjIt;
	std::vector<Tile*> converted;			// Contains tiles already changed into the biome being generated
	std::vector<Tile*>::iterator convIt;
	int index = -1;

	adjacency.push_back(getTile(coords));	// Add the specified tile to the adjacency list to start the process

	while (size--) {	// While size > 0
		index = rand() % adjacency.size();	// Index into a random tile in the adjacency list

		Tile* currentTile = adjacency.at(index);	// Track the current tile we're concerned about

		currentTile->updateProperty(biomeProperty);	// Update the property of that tile

		converted.push_back(currentTile);	// Add the tile to the converted list

		adjacency.erase(adjacency.begin() + index);		// Remove the tile from the adjacency list

		for (Tile* pNeighbour : getNeighbourTiles(currentTile, false)) {	// For each directly adjacent neighbour
			convIt = std::find(converted.begin(), converted.end(), pNeighbour);
			adjIt = std::find(adjacency.begin(), adjacency.end(), pNeighbour);

			// If converted and adjacency lists do not contain the tile, add it to adjacency list
			if (convIt == converted.end() && adjIt == adjacency.end())
				adjacency.push_back(pNeighbour);
		}
	}
}

/*
 * Returns the most recently added task in this district.
 * Returns nullptr if there are no tasks.
 */
std::shared_ptr<Task> District::getLatestTask() const {
	if (tasks.empty())
		return nullptr;

	return tasks.back();
}

/*
 * Returns the oldest task created in this district.
 * Returns nullptr if there are no tasks.
 */
std::shared_ptr<Task> District::getOldestTask() const {
	if (tasks.empty())
		return nullptr;

	return tasks.front();
}

/*
 * Prompts the district to update entities and tasks, adding and deleting where necessary.
 */
void District::update() {
	// Remove all entities that need deleting
	entities.erase(std::remove_if(entities.begin(), entities.end(), [this] (std::unique_ptr<Entity>& upE) -> bool {
		return std::find(entitiesToDelete.begin(), entitiesToDelete.end(), upE.get()) != entitiesToDelete.end();
	}), entities.end());
	entitiesToDelete.clear();

	// Add all entities that were created this game tick
	entities.insert(entities.end(), std::make_move_iterator(entitiesToAdd.begin()), std::make_move_iterator(entitiesToAdd.end()));
	entitiesToAdd.clear();

	// Remove all tasks that need deleting
	tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [this] (std::shared_ptr<Task>& upT) -> bool {
		return std::find(tasksToDelete.begin(), tasksToDelete.end(), upT.get()) != tasksToDelete.end();
	}), tasks.end());
	tasksToDelete.clear();

	// Add all tasks that were created this game tick
	tasks.insert(tasks.end(), std::make_move_iterator(tasksToAdd.begin()), std::make_move_iterator(tasksToAdd.end()));
	tasksToAdd.clear();
}

void District::deleteEntity(Entity* pEntity) {
	if (pEntity == nullptr)
		return;

	entitiesToDelete.push_back(pEntity);

	// If entity was occupying a tile, we need to tell the tile it is no longer occupied
	if (pEntity->hasComponent<PositionComponent>())
	{
		Tile* pTile = getTile(pEntity->getComponent<PositionComponent>()->getCurrentCoordinates());
		if (pTile != nullptr)
			pTile->setEntity(nullptr);
	}
}

void District::deleteTask(Tasks::Task* pTask) {
	if (pTask == nullptr)
		return;

	tasksToDelete.push_back(pTask);
}

std::string District::getName() const {
	return districtName;
}

const std::vector<std::vector<std::unique_ptr<Tile>>>& District::getTiles() const {
	return tiles;
}

/*
 * Returns the tile at the given coordinates.
 * Returns nullptr if the coordinates are out of range.
 */
Tile* District::getTile(short x, short y) const {
	return getTile(TileCoordinates(x, y));
}

/*
 * Returns the tile at the given coordinates.
 * Returns nullptr if the coordinates are out of range.
 */
Tile* District::getTile(TileCoordinates coords) const {
	if (validTileCoordinates(coords))
		return tiles[coords.x][coords.y].get();
	else
		return nullptr;
}

/**
 * Returns all valid neighbours of the given tile.
 * Diagonals are included by default. To only include directly adjacent tiles, set includeDiagonals to false.
 * Throws std::logic_error if the provided tile is nullptr.
 * The vector returned is guaranteed to be non-empty and its contents are guaranteed not to be nullptr.
 */
std::vector<Tile*> District::getNeighbourTiles(Tile* tile, bool includeDiagonals) const {
	if (tile == nullptr)
		throw std::logic_error("District::getNeighbourTiles - provided tile is nullptr");

	TileCoordinates tileCoords = tile->getCoordinates();
	std::vector<Tile*> neighbours;

	for (short x = -1; x <= 1; x++)
		for (short y = -1; y <= 1; y++)
			if (!(x == 0 && y == 0))		// Ignore the tile we're currently calculating neighbours for
			{
				TileCoordinates neighbourCoordinates(tileCoords.x + x, tileCoords.y + y);
				if (validTileCoordinates(neighbourCoordinates))	// Check we are within the bounds of the district
					if (includeDiagonals || (x == 0 || y == 0))		// Always include adjacent tiles, but only include diagonals if required
						neighbours.push_back(getTile(neighbourCoordinates));
			}

	return neighbours;
}
