#include "District.hpp"

#include "entities/Tree.hpp"
#include "entities/Sapling.hpp"
#include <algorithm>
#include "entities/Citizen.hpp"
#include "components/PositionComponent.hpp"
#include "components/TaskComponent.hpp"
#include "components/GrowComponent.hpp"
#include "entities/OccupyRules.hpp"
#include "helpers/DistrictNameGenerator.hpp"
#include <unordered_map>
#include "components/TileComponent.hpp"
#include "game/TileCoordinates.hpp"
#include "entities/Pigeon.hpp"
#include "entities/Duck.hpp"

#define BIOME_GEN true
#define TREE_GEN true
#define CITIZEN_GEN true
#define PIGEON_GEN true
#define DUCK_GEN true

District::District() : District(DistrictNameGenerator::generateName()) {}

District::District(const std::string &name) : districtName(name)
{
	PositionComponent::positionLookup = &positionLookup;
	TaskComponent::taskLookup = &taskLookup;

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
		auto citizen = makeCitizen(TileCoordinates(-1, -1));
		TileCoordinates coords(-1, -1);

		do  // Keep choosing random tiles until one is found which the entity can occupy
		{
			coords.x = rand() % District::districtSize;
			coords.y = rand() % District::districtSize;

		} while (!OccupyRules::canOccupy(this, citizen.get(), coords));

		// Place the entity on the tile
		citizen->getComponent<PositionComponent>()->setPosition(coords);
		addEntity(std::move(citizen));
	}

	if (TREE_GEN)
	{
		// Every Plains tile has a chance to grow a Tree or Sapling
		for (int x = 0; x < District::districtSize; x++)
		{
			for (int y = 0; y < District::districtSize; y++)
			{
				const TileCoordinates coords = TileCoordinates(x, y);

				if (tileMap[coords] == TileProperty::Plains)
				{
					const int treeChance = rand() % 100;
					std::unique_ptr<Entity> entity;

					if (treeChance < 2)  // 2% chance of growing a tree
					{
						entity = makeTree(TileCoordinates(-1, -1));
					}
					else if (treeChance < 10)  // 8% chance of growing a sapling
					{
						entity = makeSapling(TileCoordinates(-1, -1));
					}
					else
					{
						continue;
					}

					// Only keep the entity if it can occupy the tile
					if (OccupyRules::canOccupy(this, entity.get(), coords))
					{
						entity->getComponent<PositionComponent>()->setPosition(coords);
						addEntity(std::move(entity));
					}
				}
			}
		}
	}

	if (PIGEON_GEN)
	{
		constexpr int numPigeons = 10;
		for (int i = 0; i < numPigeons; ++i)
		{
			auto pigeon = makePigeon(TileCoordinates(-1, -1));
			TileCoordinates coords(-1, -1);

			do  // Keep choosing random tiles until one is found which the entity can occupy
			{
				coords.x = rand() % District::districtSize;
				coords.y = rand() % District::districtSize;

			} while (!OccupyRules::canOccupy(this, pigeon.get(), coords));

			// Place the entity on the tile
			pigeon->getComponent<PositionComponent>()->setPosition(coords);
			addEntity(std::move(pigeon));
		}
	}

	if (DUCK_GEN)
	{
		constexpr int numDucks = 3;
		for (int i = 0; i < numDucks; ++i)
		{
			auto duck = makeDuck(TileCoordinates(-1, -1));
			TileCoordinates coords(-1, -1);

			do  // Keep choosing random tiles until one is found which the entity can occupy
			{
				coords.x = rand() % District::districtSize;
				coords.y = rand() % District::districtSize;

			} while (!OccupyRules::canOccupy(this, duck.get(), coords));

			// Place the entity on the tile
			duck->getComponent<PositionComponent>()->setPosition(coords);
			addEntity(std::move(duck));
		}
	}
}

District::~District()
{
	PositionComponent::positionLookup = nullptr;
	TaskComponent::taskLookup = nullptr;
}

void District::addEntity(std::unique_ptr<Entity> entity)
{
	entitiesToAdd.push_back(std::move(entity));
}

Entity* District::getEntity(ID_t id) const
{
	const auto it = std::find_if(entities.begin(), entities.end(), [id](const std::unique_ptr<Entity>& e){ return e->getID() == id; });

	return (it == entities.end()) ? nullptr : (*it).get();
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

const std::unordered_set<Entity*>& District::getEntitiesAtPosition(TileCoordinates position)
{
	return positionLookup[position];
}

const std::vector<Entity*>& District::getTasks() const
{
	return taskLookup;
}
