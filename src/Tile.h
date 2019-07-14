#ifndef TILE_H_
#define TILE_H_

enum TileProperty {
	Tree,
	Water,
	WoodenWall,
	WoodenFloor,
	Plains,
	Bush,
	Rocky,
	IronOre
};

class Tile {
private:
	TileProperty properties[5];
	int xCoord, yCoord;
public:
	Tile();
	Tile(int x, int y);
	~Tile();
	void setCoordinates(int x, int y);
};

#endif /* TILE_H_ */
