#include "Constants.h"
#include "Game.h"

using std::cout;
using std::endl;
using namespace std::this_thread;
using namespace std::chrono;

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

		sleep_for(milliseconds(250));	// Wait for 1/4 of a second

		district->simulate();	// Simulate a game tick
	}

	cout << "Game Over." << endl;
}
