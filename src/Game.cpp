#include "Game.h"

using std::cout;
using std::endl;

Game::Game() {
	gameOver = false;

	map = new Map();

	cout << "New game created." << endl;
}

Game::~Game() {
	delete map;
}

void Game::play() {
	// Initialise game (create map, etc)

	// Game loop
}
