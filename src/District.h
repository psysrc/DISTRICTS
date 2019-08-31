#ifndef DISTRICT_H_
#define DISTRICT_H_

class District;

#include "Constants.h"
#include "Citizen.h"
#include "Entity.h"
#include "Tile.h"
#include <vector>
#include <algorithm>	// std::find
#include "UI.h"
#include <string>
#include "Tree.h"
#include "Sapling.h"

class District {
private:
	std::string districtName;
	Tile** tiles;
	std::vector<std::unique_ptr<Citizen>> citizens;			// All citizens in the district
	std::vector<std::unique_ptr<Entity>> entities;			// All entities in the district (not including citizens)
	std::vector<std::unique_ptr<Entity>> entitiesToAdd;		// All entities in the district (not including citizens)
public:
	District(const std::string name = "unnamed");
	~District();
	static bool validTileIndex(const int index);
	void createBiome(int i, int j, TileProperty biomeProperty, int size);
	void simulate();
	template <class E> E* makeEntity();
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

#endif /* DISTRICT_H_ */
