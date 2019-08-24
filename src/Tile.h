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
	Tile* northTile = nullptr;
	Tile* westTile = nullptr;
	Tile* eastTile = nullptr;
	Tile* southTile = nullptr;
	TileProperty property;
	Citizen* pOccupyingCitizen;
	chtype drawSymbol;
	int drawColour;
public:
	Tile();
	~Tile();
	void setDistrict(District* dist);
	void setCoordinates(int x, int y);
	void setNeighbourTiles(Tile* const n, Tile* const w, Tile* const e, Tile* const s);
	bool isInitialised() const;
	int getX() const;
	int getY() const;
	Tile* getNorthTile() const;
	Tile* getWestTile() const;
	Tile* getEastTile() const;
	Tile* getSouthTile() const;
	void updateProperty(TileProperty newProperty);
	TileProperty getProperty() const;
	District* getDistrict() const;
	void citizenEnter(Citizen* citizen);
	Citizen* citizenLeave();
	chtype getDrawSymbol() const;
	int getDrawColour() const;
	void updateVisuals();
	bool operator==(const Tile& b) const;
};

#endif /* TILE_H_ */
