#include "District.h"

#include "game/Tile.h"
#include "entities/Tree.h"
#include "entities/Sapling.h"
#include <algorithm>
#include "tasks/Task.h"
#include "entities/Citizen.h"
#include "components/PositionComponent.h"
#include "components/GrowComponent.h"

using std::string;
using std::vector;
using namespace Tasks;

District::District(const string name) : districtName(name) {
	// Define a contiguous memory space for the n*n grid of tiles
	tiles = new Tile*[DISTRICT_SIZE];
	tiles[0] = new Tile[DISTRICT_SIZE * DISTRICT_SIZE];

	// Set up the row (i) pointers
	for (int i = 1; i < DISTRICT_SIZE; i++) {
		tiles[i] = tiles[i - 1] + DISTRICT_SIZE;
	}

	// Initialise tile neighbours for each tile
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			std::vector<Tile*> neighbours;
			neighbours.reserve(8);

			for (int x = -1; x <= 1; x++)
				for (int y = -1; y <= 1; y++)
					if (!(x == 0 && y == 0)) {		// Ignore the tile we're currently calculating neighbours for
						if (validTileIndex(i + x) && validTileIndex(j + y)) {		// Check we are within the bounds of the district
							neighbours.push_back(&tiles[i + x][j + y]);
						} else {
							neighbours.push_back(nullptr);
						}
					}

			// Set neighbour for this tile
			tiles[i][j].setNeighbourTiles(neighbours);
		}
	}

	// Populate the tile grid by initialising each tile with its coordinates, district and property
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			tiles[i][j].setDistrict(this);
			tiles[i][j].setCoordinates(i, j);
			tiles[i][j].updateProperty(TileProperty::Plains);
		}
	}

	if (BIOME_GEN) {
		// Generate biomes
		int stoneBiomes = rand() % 3 + 1;	// 1-3 stone biomes
		int lakeBiomes = rand() % 3 + 1;	// 1-3 lake biomes

		while (stoneBiomes--) {
			int ri = rand() % DISTRICT_SIZE;
			int rj = rand() % DISTRICT_SIZE;
			int size = rand() % 26 + 5;		// 5-30 tiles in size

			createBiome(ri, rj, TileProperty::Stone, size);
		}

		while (lakeBiomes--) {
			int ri = rand() % DISTRICT_SIZE;
			int rj = rand() % DISTRICT_SIZE;
			int size = rand() % 101 + 10;	// 10-100 tiles in size

			createBiome(ri, rj, TileProperty::Water, size);
		}
	}

	if (TREE_GEN) {
		// Every Plains tile has a chance to grow a Tree or Sapling
		for (int i = 0; i < DISTRICT_SIZE; i++) {
			for (int j = 0; j < DISTRICT_SIZE; j++) {
				if (tiles[i][j].getProperty() == TileProperty::Plains) {
					int treeChance = rand() % 100;

					if (treeChance < 5) {	// 5% chance of growing a tree
						Tree* newTree = makeEntity<Tree>();
						newTree->getComponent<PositionComponent>()->setTile(&tiles[i][j]);
					}
					else if (treeChance < 6) {	// 1% chance of growing a sapling
						Sapling* newSapling = makeEntity<Sapling>();
						newSapling->getComponent<PositionComponent>()->setTile(&tiles[i][j]);
					}
				}
			}
		}
	}

	// Check that all tiles have been initialised
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			if (!tiles[i][j].isInitialised())
				throw UninitialisedObjectException();
		}
	}

	// Add a new citizen and place them on a walkable tile
	Citizen* citizen = makeEntity<Citizen>();

	int i, j;

	// Keep choosing random tiles until one is found in which the citizen can enter
	do {
		i = rand() % DISTRICT_SIZE;
		j = rand() % DISTRICT_SIZE;
	}
	while (!tiles[i][j].walkable());

	PositionComponent* pc = citizen->getComponent<PositionComponent>();
	if (pc != nullptr)
		pc->setTile(&tiles[i][j]);
	else
		throw std::runtime_error("Citizen does not have a PositionComponent");
}

District::~District() {
	// Delete the map tiles
	delete [] tiles[0];
	delete [] tiles;
}

const std::vector<std::unique_ptr<Entity>>& District::getEntities() const {
	return entities;
}

/*
 * Returns whether or not an index into the Tiles array is valid.
 */
bool District::validTileIndex(const int index) {
	return (index >= 0 && index < DISTRICT_SIZE);
}

/*
 * Creates/adds a new biome to the district at a given location, with a defined size
 */
void District::createBiome(int i, int j, TileProperty::TileProperty biomeProperty, int size) {
	std::vector<Tile*> adjacency;			// Contains tiles adjacent to converted tiles
	std::vector<Tile*>::iterator adjIt;
	std::vector<Tile*> converted;			// Contains tiles already changed into the biome being generated
	std::vector<Tile*>::iterator convIt;
	int index = -1;

	adjacency.push_back(&tiles[i][j]);	// Add the specified tile to the adjacency list to start the process

	while (size--) {	// While size > 0
		index = rand() % adjacency.size();	// Index into a random tile in the adjacency list

		Tile& currentTile = *adjacency.at(index);	// Track the current tile we're concerned about

		currentTile.updateProperty(biomeProperty);	// Update the property of that tile

		converted.push_back(&currentTile);	// Add the tile to the converted list

		adjacency.erase(adjacency.begin() + index);		// Remove the tile from the adjacency list

		// Get the 4 neighbouring tiles
		Tile* neighbours[4];
		neighbours[0] = currentTile.getNeighbourTile(North);
		neighbours[1] = currentTile.getNeighbourTile(West);
		neighbours[2] = currentTile.getNeighbourTile(East);
		neighbours[3] = currentTile.getNeighbourTile(South);

		for (int n = 0; n < 4; n++) {	// For each neighbour
			if (neighbours[n] != nullptr) {		// If adjacent tile is within bounds
				convIt = std::find(converted.begin(), converted.end(), neighbours[n]);
				adjIt = std::find(adjacency.begin(), adjacency.end(), neighbours[n]);

				// If converted and adjacency lists do not contain the tile, add it to adjacency list
				if (convIt == converted.end() && adjIt == adjacency.end())
					adjacency.push_back(neighbours[n]);
			}
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
 * Prompts the district to simulate one game tick.
 */
void District::simulate() {
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

void District::deleteEntity(Entity* entity) {
	entitiesToDelete.push_back(entity);
}

void District::deleteTask(Tasks::Task* task) {
	tasksToDelete.push_back(task);
}

string District::getName() const {
	return districtName;
}

Tile** District::getTiles() const {
	return tiles;
}

/*
 * Returns the tile at the given coordinates.
 * Returns nullptr if the coordinates are out of range.
 */
Tile* District::getTile(const int i, const int j) const {
	if (validTileIndex(i) && validTileIndex(j))
		return &tiles[i][j];
	else
		return nullptr;
}
