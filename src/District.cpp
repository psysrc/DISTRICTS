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

	int stoneBiomes = rand() % 3 + 1;	// 1-3 stone biomes
	int lakeBiomes = rand() % 4;		// 0-3 lake biomes

	while (stoneBiomes--) {
		int ri = rand() % DISTRICT_SIZE;
		int rj = rand() % DISTRICT_SIZE;
		int size = rand() % 26 + 5;		// 5-30 tiles in size

		createBiome(ri, rj, Stone, size);
	}

	while (lakeBiomes--) {
		int ri = rand() % DISTRICT_SIZE;
		int rj = rand() % DISTRICT_SIZE;
		int size = rand() % 101 + 10;	// 10-100 tiles in size

		createBiome(ri, rj, Water, size);
	}

	// Every Plains tile has a chance to become a Tree tile
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			if (tiles[i][j].getProperty() == Plains) {
				int treeChance = rand() % 100;

				if (treeChance < 5)	// 5% chance of growing a tree
					tiles[i][j].updateProperty(Tree);
			}
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
	// Delete the map tiles
	delete [] tiles[0];
	delete [] tiles;

	for (Citizen* c : citizens) {	// Delete all citizen objects
		delete c;
	}

	citizens.clear();	// Delete the citizens vector
}

/*
 * Creates/adds a new biome to the district at a given location, with a defined size
 */
void District::createBiome(int i, int j, TileProperty biomeProperty, int size) {
	std::vector<Tile*> adjacency;
	std::vector<Tile*>::iterator adjIt;
	std::vector<Tile*> converted;
	std::vector<Tile*>::iterator convIt;
	int index = -1;

	adjacency.push_back(&tiles[i][j]);	// Add the specified tile to the adjacency list to start the process

	while (size--) {	// While size > 0
		index = rand() % adjacency.size();	// Index into a random tile in the adjacency list

		Tile& currentTile = *adjacency.at(index);	// Track the current tile we're concerned about

		currentTile.updateProperty(biomeProperty);	// Update the property of that tile

		converted.push_back(&currentTile);	// Add the tile to the converted list

		adjacency.erase(adjacency.begin() + index);		// Remove the tile from the adjacency list

		int cx = currentTile.getX();
		int cy = currentTile.getY();

		// Define the neighbour coordinates from the current tile
		int ais[4] = {cx - 1, cx, cx, cx + 1};
		int ajs[4] = {cy, cy - 1, cy + 1, cy};

		for (int n = 0; n < 4; n++) {	// For each neighbour
			if (ais[n] >= 0 && ais[n] < DISTRICT_SIZE && ajs[n] >= 0 && ajs[n] < DISTRICT_SIZE) {	// If adjacent tile is within bounds
				convIt = std::find(converted.begin(), converted.end(), &tiles[ais[n]][ajs[n]]);
				adjIt = std::find(adjacency.begin(), adjacency.end(), &tiles[ais[n]][ajs[n]]);

				// If converted and adjacency lists do not contain the tile, add it to adjacency list
				if (convIt == converted.end() && adjIt == adjacency.end())
					adjacency.push_back(&tiles[ais[n]][ajs[n]]);
			}
		}
	}
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
void District::draw(WINDOW* mapWindow) const {
	wmove(mapWindow, 0, 0);	// Move the cursor to the window origin

	// Draw the N*N grid of tiles
	// The cursor will automatically wrap to the next line when it reaches the end of the window
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			int tileColour = tiles[i][j].getDrawColour();

			wattron(mapWindow, COLOR_PAIR(tileColour));
			waddch(mapWindow, tiles[i][j].getDrawSymbol());
			waddch(mapWindow, ' ');
			wattroff(mapWindow, COLOR_PAIR(tileColour));
		}
	}
}

string District::getName() const {
	return districtName;
}

Tile** District::getTiles() const {
	return tiles;
}

/*
 * Returns the tile at the given coordinates.
 * Returns nullptr if the coordinates are out of range.
 */
Tile* District::getTile(const int i, const int j) const {
	if (i < 0 || i >= DISTRICT_SIZE || j < 0 || j >= DISTRICT_SIZE)	// Check the indexes are in range
		return nullptr;
	else
		return &tiles[i][j];
}
