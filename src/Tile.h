#ifndef TILE_H_
#define TILE_H_

#include <iostream>

using namespace std;

class Tile {
private:
	int xCoord, yCoord;
public:
	Tile();
	Tile(int x, int y);
	~Tile();
	void setCoordinates(int x, int y);
};

#endif /* TILE_H_ */
