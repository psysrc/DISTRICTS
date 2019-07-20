#ifndef TILE_H_
#define TILE_H_

enum TileProperty {
	Tree,
	Water,
	Grass,
	Stone
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
