#ifndef TILE_H_
#define TILE_H_

#include <vector>
#include "game/Constants.h"

class District;
class Entity;
class Citizen;

class Tile {
private:
	District* pDistrict;
	int xCoord, yCoord;
	std::vector<Tile*> neighbourTiles;
	Entity* pEntity;
	TileProperty::TileProperty property;
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
	void updateProperty(TileProperty::TileProperty newProperty);
	TileProperty::TileProperty getProperty() const;
	Entity* getEntity() const;
	District* getDistrict() const;
	bool walkable() const;
	bool citizenEnter(Citizen*);
	bool occupy(Entity*);
	Entity* vacateEntity();
	bool occupied() const;
	int getDrawColour() const;
	void updateVisuals();
	bool operator==(const Tile& b) const;
};

#endif /* TILE_H_ */
