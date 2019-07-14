#include "Map.h"

Map::Map() {
	// Define a contiguous memory space for the n*n grid of tiles
	tiles = new Tile*[MAP_SIZE];
	tiles[0] = new Tile[MAP_SIZE * MAP_SIZE];


	for (int i = 1; i < MAP_SIZE; i++) {
		tiles[i] = tiles[i - 1] + MAP_SIZE;
	}

	// Populate the tile grid by initialising each tile with its coordinates
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			tiles[i][j].setCoordinates(i, j);
		}
	}
}

Map::~Map() {
	delete [] tiles[0];
	delete [] tiles;
}
