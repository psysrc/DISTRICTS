#include "Game.h"

using std::cout;
using std::endl;

Game::Game() {
	gameOver = false;

	district = new District();

	cout << "New game created." << endl;
}

Game::~Game() {
	delete district;
}

void Game::play() {
	// Initialise game (create map, etc)

	// Game loop
}
