#include "Constants.h"
#include "Game.h"

using std::cout;
using std::endl;
using namespace std::this_thread;
using namespace std::chrono;

Game::Game() {
	gameIsOver = false;

	pDistrict = new District();

	if (DEBUG)
		cout << "New game created." << endl;
}

Game::~Game() {
	delete pDistrict;
}

/*
 * Defines the game loop while the game is still being played (game isn't over).
 */
void Game::play() {
	// Game loop
	while (!gameIsOver) {
		// If user has paused:
		// 	Wait for their input
		// 	If they provide input (without unpausing), process it

		sleep_for(milliseconds(250));	// Wait for 1/4 of a second

		if (DEBUG)
			cout << "Simulating district " << pDistrict->getName() << endl;

		pDistrict->simulate();	// Simulate a game tick

		// TODO: Render the game state
		drawGameState();
	}

	gameOver();
}

/*
 * Draws the current state of the game.
 */
void Game::drawGameState() {
	cout << pDistrict->draw() << endl;
}

/*
 * This method is called when the game is over.
 */
void Game::gameOver() {
	cout << "Game Over." << endl;
}
