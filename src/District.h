#ifndef DISTRICT_H_
#define DISTRICT_H_

class District;

#include "Constants.h"
#include "Citizen.h"
#include "Tile.h"
#include <vector>
#include <exception>
#include <ncurses.h>

using std::string;
using std::vector;

#define DISTRICT_SIZE 32

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
	void draw(WINDOW* mapWindow);
	string getName();
	Tile** getTiles();
	Tile* getTile(const int i, const int j);
};

#endif /* DISTRICT_H_ */
