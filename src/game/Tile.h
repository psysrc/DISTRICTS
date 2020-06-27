#ifndef TILE_H_
#define TILE_H_

#include <vector>
#include "game/Constants.h"

class Entity;

struct TileCoordinates {
	TileCoordinates(const unsigned short x, const unsigned short y) : x(x), y(y) {}
	~TileCoordinates() {}
	unsigned short x;
	unsigned short y;
};

class Tile {
private:
	TileCoordinates coordinates;
	std::vector<Tile*> neighbourTiles;
	Entity* pEntity;
	TileProperty::TileProperty property;
	int drawColour;
public:
	Tile();
	~Tile();
	void setCoordinates(const TileCoordinates);
	void setNeighbourTiles(const std::vector<Tile*> neighbours);
	bool isInitialised() const;
	int getX() const;
	int getY() const;
	Tile* getNeighbourTile(int direction) const;
	void updateProperty(TileProperty::TileProperty newProperty);
	TileProperty::TileProperty getProperty() const;
	Entity* getEntity() const;
	bool walkable() const;
	bool occupy(Entity*);
	Entity* vacateEntity();
	bool occupied() const;
	int getDrawColour() const;
	void updateColour();
	bool operator==(const Tile& b) const;
};

#endif /* TILE_H_ */
