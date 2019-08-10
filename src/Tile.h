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
	bool isInitialised() const;
	int getX() const;
	int getY() const;
	void updateProperty(TileProperty newProperty);
	TileProperty getProperty() const;
	District* getDistrict() const;
	void citizenEnter(Citizen* citizen);
	Citizen* citizenLeave();
	chtype draw() const;
	bool operator==(const Tile& b) const;
};

#endif /* TILE_H_ */
