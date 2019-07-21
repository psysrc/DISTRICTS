#include "Constants.h"
#include "Game.h"

using std::cout;
using std::endl;

Game::Game() {
	gameOver = false;

	district = new District();

	if (DEBUG)
		cout << "New game created." << endl;
}

Game::~Game() {
	delete district;
}

void Game::play() {
	// Game loop
	while (!gameOver) {
		// If user has paused:
		// 	Wait for their input
		// 	If they provide input (without unpausing), process it
		// Otherwise continue:
		// Wait for some milliseconds
		// Simulate a game tick
	}

	cout << "Game Over." << endl;
}
