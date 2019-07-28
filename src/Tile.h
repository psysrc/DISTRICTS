#ifndef TILE_H_
#define TILE_H_

class Tile;

#include "District.h"
#include "Citizen.h"
#include <vector>

using std::vector;
using std::string;

enum TileProperty {
	Tree,
	Water,
	Grass,
	Stone
};

class Tile {
private:
	District* pDistrict;
	int xCoord, yCoord;
	vector<TileProperty> properties;
	Citizen* pOccupyingCitizen;
public:
	Tile();
	~Tile();
	void setDistrict(District* dist);
	void setCoordinates(int x, int y);
	int getX();
	int getY();
	District* getDistrict();
	void citizenEnter(Citizen* citizen);
	Citizen* citizenLeave();
	string draw();
};

#endif /* TILE_H_ */
