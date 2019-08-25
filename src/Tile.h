#ifndef TILE_H_
#define TILE_H_

class Tile;

#include "District.h"
#include <memory>
#include "Entity.h"

class Tile {
private:
	District* pDistrict;
	int xCoord, yCoord;
	Tile* northTile = nullptr;
	Tile* westTile = nullptr;
	Tile* eastTile = nullptr;
	Tile* southTile = nullptr;
	Entity* pEntity;
	TileProperty property;
	char drawSymbol;
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
	Tile* const getNeighbourTile(MoveDirection direction) const;
	void updateProperty(TileProperty newProperty);
	TileProperty getProperty() const;
	District* getDistrict() const;
	bool citizenEnter(Citizen*);
	bool occupy(Entity*);
	void vacateEntity();
	bool occupied() const;
	char getDrawSymbol() const;
	int getDrawColour() const;
	void updateVisuals();
	bool operator==(const Tile& b) const;
};

#endif /* TILE_H_ */
