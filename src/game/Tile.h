#ifndef TILE_H_
#define TILE_H_

#include <vector>
#include "game/Constants.h"

class District;
class Entity;

struct TileCoordinates {
	TileCoordinates(short x, short y) : x(x), y(y) {}

	~TileCoordinates() {}

	bool operator==(const TileCoordinates& b) const {
		return (x == b.x) && (y == b.y);
	}

	bool operator!=(const TileCoordinates& b) const {
		return !(*this == b);
	}

	short x;
	short y;
};

class Tile {
private:
	TileCoordinates coordinates;
	Entity* pEntity;
	TileProperty::TileProperty property;
	int drawColour;
public:
	Tile(TileCoordinates, TileProperty::TileProperty);
	~Tile();
	TileCoordinates getCoordinates() const;
	void updateProperty(TileProperty::TileProperty newProperty);
	TileProperty::TileProperty getProperty() const;
	Entity* getEntity() const;
	void setEntity(Entity*);
	int getDrawColour() const;
	void updateColour();
	bool operator==(const Tile& b) const;
};

#endif /* TILE_H_ */
