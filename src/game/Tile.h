#ifndef TILE_H_
#define TILE_H_

#include "Constants.h"
#include "entities/Entity.h"
#include "entities/Citizen.h"
#include <vector>
#include <stdexcept>
#include "District.h"

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
	Tile* getNeighbourTile(int direction) const;
	void updateProperty(TileProperty newProperty);
	TileProperty getProperty() const;
	District* getDistrict() const;
	bool walkable() const;
	bool citizenEnter(Citizen*);
	bool occupy(Entity*);
	Entity* vacateEntity();
	bool occupied() const;
	char getDrawSymbol() const;
	int getDrawColour() const;
	void updateVisuals();
	bool operator==(const Tile& b) const;
};

#endif /* TILE_H_ */
