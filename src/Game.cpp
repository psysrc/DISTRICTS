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
	int i = 10000;

	// Game loop
	while (!gameOver) {
		if (i--)
			gameOver = true;
	}

	cout << "Game Over." << endl;
}
