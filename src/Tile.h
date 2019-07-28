#ifndef TILE_H_
#define TILE_H_

class Tile;

#include "District.h"
#include "Citizen.h"
#include <vector>

using std::vector;
using std::string;

enum TileProperty {
	Plains,
	Water,
	Stone,
	Tree
};

class Tile {
private:
	District* pDistrict;
	int xCoord, yCoord;
	TileProperty property;
	Citizen* pOccupyingCitizen;
public:
	Tile();
	~Tile();
	void setDistrict(District* dist);
	void setCoordinates(int x, int y);
	bool isInitialised();
	int getX();
	int getY();
	void updateProperty(TileProperty newProperty);
	TileProperty getProperty();
	District* getDistrict();
	void citizenEnter(Citizen* citizen);
	Citizen* citizenLeave();
	string draw();
};

#endif /* TILE_H_ */
