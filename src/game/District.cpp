#include "District.h"

#include "entities/Tree.h"
#include "entities/Sapling.h"
#include <algorithm>
#include "entities/Citizen.h"
#include "components/PositionComponent.h"
#include "components/GrowComponent.h"
#include "entities/OccupyRules.h"
#include "helpers/DistrictNameGenerator.h"
#include <unordered_map>
#include <components/TileComponent.h>
#include "game/TileCoordinates.h"

#define BIOME_GEN true
#define TREE_GEN true
#define CITIZEN_GEN true

District::District() : District(DistrictNameGenerator::generateName()) {}

District::District(const std::string &name) : districtName(name)
{
	PositionComponent::positionLookup = &positionLookup;

	auto tileMap = std::unordered_map<TileCoordinates, TileProperty::TileProperty>();
	for (int y = 0; y < District::districtSize; y++)
	{
		for (int x = 0; x < District::districtSize; x++)
		{
			tileMap[TileCoordinates(x, y)] = TileProperty::Plains;
		}
	}

	if (BIOME_GEN)
	{
		// Generate biomes
		int stoneBiomes = rand() % 3 + 1; // 1-3 stone biomes
		int lakeBiomes = rand() % 3 + 1;  // 1-3 lake biomes

		while (stoneBiomes--)
		{
			int ri = rand() % District::districtSize;
			int rj = rand() % District::districtSize;
			int size = rand() % 26 + 5; // 5-30 tiles in size

			createBiome(TileCoordinates(ri, rj), TileProperty::Stone, size, tileMap);
		}

		while (lakeBiomes--)
		{
			int ri = rand() % District::districtSize;
			int rj = rand() % District::districtSize;
			int size = rand() % 101 + 10; // 10-100 tiles in size

			createBiome(TileCoordinates(ri, rj), TileProperty::Water, size, tileMap);
		}
	}

	for (auto tileData : tileMap)
	{
		auto tile = std::make_unique<Entity>();
		tile->addComponent(std::make_unique<PositionComponent>(tileData.first, tile.get()));
		tile->addComponent(std::make_unique<TileComponent>(tileData.second));

		addEntity(std::move(tile));
	}

	if (CITIZEN_GEN)
	{
		int citizenX = -1, citizenY = -1;
		Entity* citizenTile = nullptr;

		// Make a new citizen and place them on a walkable tile
		auto citizen = makeCitizen(TileCoordinates(-1, -1));

		// Keep choosing random tiles until one is found in which the citizen can enter
		do
		{
			citizenX = rand() % District::districtSize;
			citizenY = rand() % District::districtSize;
			const auto& entities = entitiesAtPosition(TileCoordinates(citizenX, citizenY));
			const auto it = std::find_if(entities.begin(), entities.end(), [](Entity* e){ return e->hasComponent<TileComponent>(); });

			if (it == entities.end())
			{
				throw std::runtime_error("No tile entities at some random position");
			}

			citizenTile = *it;

		} while (!OccupyRules::canOccupy(this, citizenTile));

		citizen->getComponent<PositionComponent>()->setPosition(TileCoordinates(citizenX, citizenY));
		addEntity(std::move(citizen));
	}

	if (TREE_GEN)
	{
		// Every Plains tile has a chance to grow a Tree or Sapling, as long as the Citizen isn't already occupying it
		for (int x = 0; x < District::districtSize; x++)
		{
			for (int y = 0; y < District::districtSize; y++)
			{
				if (OccupyRules::canOccupy(this, TileCoordinates(x, y)) && tileMap[TileCoordinates(x, y)] == TileProperty::Plains)
				{
					int treeChance = rand() % 100;

					if (treeChance < 2)  // 2% chance of growing a tree
					{
						auto tree = makeTree(TileCoordinates(x, y));
						addEntity(std::move(tree));
					}
					else if (treeChance < 10)  // 8% chance of growing a sapling
					{
						auto sapling = makeSapling(TileCoordinates(x, y));
						addEntity(std::move(sapling));
					}
				}
			}
		}
	}
}

District::~District()
{
	PositionComponent::positionLookup = nullptr;
}

void District::addEntity(std::unique_ptr<Entity> entity)
{
	entitiesToAdd.push_back(std::move(entity));
}

const std::vector<std::unique_ptr<Entity>> &District::getEntities() const
{
	return entities;
}

/*
 * Returns whether or not a set of Tile coordinates is valid.
 */
bool District::validTileCoordinates(TileCoordinates coords)
{
	return coords.x >= 0 && coords.x < districtSize && coords.y >= 0 && coords.y < districtSize;
}

/*
 * Creates/adds a new biome to the district at a given location, with a defined size
 */
void District::createBiome(TileCoordinates coords, TileProperty::TileProperty biomeProperty, int size, std::unordered_map<TileCoordinates, TileProperty::TileProperty>& tileMap)
{
	if (!validTileCoordinates(coords))
		throw std::logic_error("District::createBiome - Invalid coordinates");

	std::vector<TileCoordinates> adjacency; // Contains tiles adjacent to converted tiles
	std::vector<TileCoordinates>::iterator adjIt;
	std::vector<TileCoordinates> converted; // Contains tiles already changed into the biome being generated
	std::vector<TileCoordinates>::iterator convIt;
	int index = -1;

	adjacency.push_back(coords); // Add the specified tile to the adjacency list to start the process

	while (size--)  // While size > 0
	{
		index = rand() % adjacency.size(); // Index into a random tile in the adjacency list

		TileCoordinates currentCoordinates = adjacency.at(index); // Track the current tile we're concerned about

		tileMap[currentCoordinates] = biomeProperty;  // Update the property of those coordinates

		converted.push_back(currentCoordinates); // Add the tile to the converted list

		adjacency.erase(adjacency.begin() + index); // Remove the tile from the adjacency list

		for (TileCoordinates neighbour : getNeighbourCoordinates(currentCoordinates, false))  // For each directly adjacent neighbour
		{
			convIt = std::find(converted.begin(), converted.end(), neighbour);
			adjIt = std::find(adjacency.begin(), adjacency.end(), neighbour);

			// If converted and adjacency lists do not contain the tile, add it to adjacency list
			if (convIt == converted.end() && adjIt == adjacency.end())
				adjacency.push_back(neighbour);
		}
	}
}

/*
 * Prompts the district to update entities and tasks, adding and deleting where necessary.
 */
void District::update()
{
	// Remove all entities that need deleting
	entities.erase(std::remove_if(entities.begin(), entities.end(), [this](std::unique_ptr<Entity> &upE) -> bool
								  { return std::find(entitiesToDelete.begin(), entitiesToDelete.end(), upE.get()) != entitiesToDelete.end(); }),
				   entities.end());
	entitiesToDelete.clear();

	// Add all entities that were created this game tick
	entities.insert(entities.end(), std::make_move_iterator(entitiesToAdd.begin()), std::make_move_iterator(entitiesToAdd.end()));
	entitiesToAdd.clear();
}

void District::deleteEntity(Entity *pEntity)
{
	if (pEntity == nullptr)
		return;

	entitiesToDelete.push_back(pEntity);
}

std::string District::getName() const
{
	return districtName;
}

std::vector<TileCoordinates> District::getNeighbourCoordinates(TileCoordinates coordinates, bool includeDiagonals) const
{
	std::vector<TileCoordinates> neighbours;

	for (short x = -1; x <= 1; x++)
		for (short y = -1; y <= 1; y++)
			if (!(x == 0 && y == 0)) // Ignore the original coordinates
			{
				TileCoordinates neighbourCoordinates(coordinates.x + x, coordinates.y + y);
				if (validTileCoordinates(neighbourCoordinates)) // Check we are within the bounds of the district
					if (includeDiagonals || (x == 0 || y == 0)) // Always include adjacent tiles, but only include diagonals if required
						neighbours.push_back(neighbourCoordinates);
			}

	return neighbours;
}

const std::unordered_set<Entity*>& District::entitiesAtPosition(TileCoordinates position)
{
	return positionLookup[position];
}
