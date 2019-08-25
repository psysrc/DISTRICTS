#ifndef DISTRICT_H_
#define DISTRICT_H_

class District;

#include "Constants.h"
#include "Citizen.h"
#include "Entity.h"
#include "Tile.h"
#include <vector>
#include <algorithm>	// std::find
#include "UserInterface.h"
#include <string>
#include "Tree.h"
#include "Sapling.h"

class District {
private:
	std::string districtName;
	Tile** tiles;
	std::vector<std::unique_ptr<Citizen>> citizens;		// All citizens in the district
	std::vector<std::unique_ptr<Entity>> entities;		// All entities in the district (not including citizens)
public:
	District(const std::string name = "unnamed");
	~District();
	bool validTileIndex(const int index) const;
	void createBiome(int i, int j, TileProperty biomeProperty, int size);
	void simulate();
	std::string getName() const;
	Tile** getTiles() const;
	Tile* getTile(const int i, const int j) const;
};

#endif /* DISTRICT_H_ */
