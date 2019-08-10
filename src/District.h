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

using std::string;
using std::vector;

class District {
private:
	string districtName;
	Tile** tiles;
	vector<Citizen*> citizens;
public:
	District();
	District(const string name);
	~District();
	void createBiome(int i, int j, TileProperty biomeProperty, int size);
	void simulate();
	void draw(WINDOW* mapWindow) const;
	string getName() const;
	Tile** getTiles() const;
	Tile* getTile(const int i, const int j) const;
};

#endif /* DISTRICT_H_ */
