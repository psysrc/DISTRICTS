#include "District.h"

District::District() : District("unnamed") {

}

District::District(string name) : districtName(name) {
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
	for (Citizen* c : citizens) {
		if (DEBUG)
			cout << "Simulating citizen " << c->getName() << endl;

		c->takeAction();
	}

	// Simulate the rest of the district
}

/*
 * Used by the game to draw the district to the screen when required.
 */
string District::draw() {
	std::stringstream ss;

	ss << "This is placeholder text for a drawing of the '" << districtName << "' district." << endl;

	return ss.str();
}

string District::getName() {
	return districtName;
}
