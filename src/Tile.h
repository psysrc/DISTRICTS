#ifndef TILE_H_
#define TILE_H_

class Tile;

#include "District.h"
#include "Citizen.h"
#include <vector>
#include <ncurses.h>

using std::vector;
using std::string;

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
	chtype draw();
};

#endif /* TILE_H_ */
