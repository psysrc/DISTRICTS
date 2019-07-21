#ifndef TILE_H_
#define TILE_H_

#include <vector>

using std::vector;

enum TileProperty {
	Tree,
	Water,
	Grass,
	Stone
};

class Tile {
private:
	vector<TileProperty> properties;
	int xCoord, yCoord;
public:
	Tile();
	Tile(int x, int y);
	~Tile();
	void setCoordinates(int x, int y);
};

#endif /* TILE_H_ */
