#include "Constants.h"
#include "Game.h"

using std::cout;
using std::endl;
using namespace std::this_thread;
using namespace std::chrono;

Game::Game() {
	gameIsOver = false;

	district = new District();

	if (DEBUG)
		cout << "New game created." << endl;
}

Game::~Game() {
	delete district;
}

void Game::play() {
	// Game loop
	while (!gameIsOver) {
		// If user has paused:
		// 	Wait for their input
		// 	If they provide input (without unpausing), process it

		sleep_for(milliseconds(250));	// Wait for 1/4 of a second

		if (DEBUG)
			cout << "Simulating district " << district->getName() << endl;

		district->simulate();	// Simulate a game tick

		// TODO: Render the game state to the console
	}

	gameOver();
}

/*
 * This method is called when the game is over.
 */
void Game::gameOver() {
	cout << "Game Over." << endl;
}
