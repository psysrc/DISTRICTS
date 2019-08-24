#ifndef DISTRICT_H_
#define DISTRICT_H_

class District;

#include "Constants.h"
#include "Citizen.h"
#include "Tile.h"
#include <vector>
#include <exception>
#include <ncurses.h>
#include <algorithm>	// std::find
#include "UserInterface.h"

using std::string;
using std::vector;

class District {
private:
	string districtName;
	Tile** tiles;
	vector<Citizen*> citizens;
public:
	District(const string name = "unnamed");
	~District();
	bool validTileIndex(const int index) const;
	void createBiome(int i, int j, TileProperty biomeProperty, int size);
	void simulate();
	string getName() const;
	Tile** getTiles() const;
	Tile* getTile(const int i, const int j) const;
};

#endif /* DISTRICT_H_ */
