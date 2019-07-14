#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include "Tile.h"

using namespace std;

#define MAP_SIZE 10

class Map {
private:
	Tile** tiles;
public:
	Map();
	~Map();
};

#endif /* MAP_H_ */
