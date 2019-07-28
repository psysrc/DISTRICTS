#include "District.h"

District::District() : District("unnamed") {

}

District::District(string name) : districtName(name) {
	// Define a contiguous memory space for the n*n grid of tiles
	tiles = new Tile*[DISTRICT_SIZE];
	tiles[0] = new Tile[DISTRICT_SIZE * DISTRICT_SIZE];

	// Set up the row (i) pointers
	for (int i = 1; i < DISTRICT_SIZE; i++) {
		tiles[i] = tiles[i - 1] + DISTRICT_SIZE;
	}

	// Populate the tile grid by initialising each tile with its coordinates and district
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			tiles[i][j].setDistrict(this);
			tiles[i][j].setCoordinates(i, j);
		}
	}

	// Check that all tiles have been initialised
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			if (!tiles[i][j].isInitialised())
				throw UninitialisedObjectException();
		}
	}

	// Add a new citizen to tile [1, 1]
	Citizen* newCitizen = new Citizen("Geoff");
	citizens.push_back(newCitizen);
	tiles[1][1].citizenEnter(newCitizen);
}

District::~District() {
	delete [] tiles[0];
	delete [] tiles;

	for (Citizen* c : citizens) {
		delete c;
	}

	citizens.clear();
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

	// TODO: Simulate the rest of the district
}

/*
 * Used by the game to draw the district to the screen when required.
 */
string District::draw() {
	std::stringstream ss;

	// Draw the N*N grid of tiles
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			ss << tiles[i][j].draw() << " ";
		}

		ss << endl;
	}

	return ss.str();
}

string District::getName() {
	return districtName;
}

Tile** District::getTiles() {
	return tiles;
}

/*
 * Returns the tile at the given coordinates.
 * Returns nullptr if the coordinates are out of range.
 */
Tile* District::getTile(const int i, const int j) {
	if (i < 0 || i >= DISTRICT_SIZE || j < 0 || j >= DISTRICT_SIZE)	// Check the indexes are in range
		return nullptr;
	else
		return &tiles[i][j];
}
