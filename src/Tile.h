#ifndef TILE_H_
#define TILE_H_

#include "Citizen.h"
#include <vector>

using std::vector;

enum TileProperty {
	Tree,
	Water,
	Grass,
	Stone
};

class Tile {
private:
	int xCoord, yCoord;
	vector<TileProperty> properties;
	Citizen* occupyingCitizen;
public:
	Tile();
	Tile(int x, int y);
	~Tile();
	void setCoordinates(int x, int y);
	string draw();
};

#endif /* TILE_H_ */
