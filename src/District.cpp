#include "District.h"

District::District() {
	citizens = nullptr;

	// Define a contiguous memory space for the n*n grid of tiles
	tiles = new Tile*[DISTRICT_SIZE];
	tiles[0] = new Tile[DISTRICT_SIZE * DISTRICT_SIZE];


	for (int i = 1; i < DISTRICT_SIZE; i++) {
		tiles[i] = tiles[i - 1] + DISTRICT_SIZE;
	}

	// Populate the tile grid by initialising each tile with its coordinates
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			tiles[i][j].setCoordinates(i, j);
		}
	}
}

District::~District() {
	delete [] tiles[0];
	delete [] tiles;
}

/*
 * Prompts the district to simulate one game tick.
 */
void District::simulate() {
	// Simulate all citizens
	if (citizens != nullptr) {
		for (Citizen* c : citizens) {
			c->takeAction();
		}
	}

	// Simulate the rest of the district
}
