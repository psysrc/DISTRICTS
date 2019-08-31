#ifndef TILE_H_
#define TILE_H_

#include "Constants.h"
#include "Entity.h"
#include "Citizen.h"
#include <vector>

// No need to fully include
class District;

class Tile {
private:
	District* pDistrict;
	int xCoord, yCoord;
	std::vector<Tile*> neighbourTiles;
	Entity* pEntity;
	TileProperty property;
	char drawSymbol;
	int drawColour;
public:
	Tile();
	~Tile();
	void setDistrict(District* dist);
	void setCoordinates(int x, int y);
	void setNeighbourTiles(const std::vector<Tile*> neighbours);
	bool isInitialised() const;
	int getX() const;
	int getY() const;
	Tile* const getNeighbourTile(int direction) const;
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
