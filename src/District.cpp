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

	// Populate the tile grid by initialising each tile with its coordinates, district and property
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			tiles[i][j].setDistrict(this);
			tiles[i][j].setCoordinates(i, j);
			tiles[i][j].updateProperty(Plains);
		}
	}

	// TODO: Add random biomes to the district
	/*
	 * At least 1 stoney area
	 * Potentially up to 4
	 * At least 10 blocks in size
	 * No more than 50 blocks size
	 *
	 * At most 1 ocean biome
	 * Up to 3 lake biomes
	 */

	int stoneBiomes = rand() % 4 + 1;
	int oceanBiomes = rand() % 2;
	int lakeBiomes = rand() % 4;

	while (stoneBiomes--) {
		/*
		 * Pick a random point in the district and add it to adjacent tiles
		 * do:
		 * 		Pick a random adjacent tile
		 * 		Make it stone
		 * 		Update adjacent tiles
		 * until no more blocks to make
		 */
	}

	while (oceanBiomes--) {
		/*
		 * Make one side of the district water
		 * Perform same adjacency creation as stone
		 */
	}

	while (lakeBiomes--) {
		/*
		 * Same as stone creation
		 */
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
	// Delete the map tiles
	delete [] tiles[0];
	delete [] tiles;

	for (Citizen* c : citizens) {	// Delete all citizen objects
		delete c;
	}

	citizens.clear();	// Delete the citizens vector
}

/*
 * Prompts the district to simulate one game tick.
 */
void District::simulate() {
	// Simulate all citizens
	for (Citizen* c : citizens) {
		// TODO: Use Game::DisplayDebugMessage()
//		if (DEBUG)
//			cout << "Simulating citizen " << c->getName() << endl;

		c->takeAction();
	}

	// TODO: Simulate the rest of the district
}

/*
 * Draws the district to the map window when the game requires it.
 */
void District::draw(WINDOW* mapWindow) {
	wmove(mapWindow, 0, 0);	// Move the cursor to the window origin

	// Draw the N*N grid of tiles
	// The cursor will automatically wrap to the next line when it reaches the end of the window
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			waddch(mapWindow, tiles[i][j].draw());
			waddch(mapWindow, ' ');
		}
	}
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
