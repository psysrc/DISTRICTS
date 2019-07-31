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

	initscr();	// Prepare the terminal window for Ncurses-style output

	// Define the windows in the terminal
	mapWindow = newwin(DISTRICT_SIZE, DISTRICT_SIZE * 2, 0, 0);
	activityWindow = newwin(10, DISTRICT_SIZE * 2, DISTRICT_SIZE + 2, 0);
	debugWindow = newwin(DISTRICT_SIZE, 40, 0, (DISTRICT_SIZE * 2) + 4);

	scrollok(activityWindow, TRUE);
}

Game::~Game() {
	delete pDistrict;

	delete mapWindow;
	delete activityWindow;
	delete debugWindow;

	endwin();	// End of Ncurses activity
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

//		if (DEBUG)
//			cout << "Simulating district " << pDistrict->getName() << endl;

		pDistrict->simulate();	// Simulate a game tick

		// Render the game state to the user
		UpdateUI();
	}

	gameOver();
}

/**
 * Prints a string to the Activity window.
 */
void Game::displayActivityMessage(const char* str) {
	wmove(activityWindow, activityWindow->_maxy, 0);	// Move to the bottom line of the window
	waddstr(activityWindow, str);						// Print the line
	waddstr(activityWindow, "\n");						// Carriage return to scroll the window up
}

/**
 * Prints a string to the Debug window.
 */
void Game::displayDebugMessage(const char* str) {
	wmove(debugWindow, debugWindow->_maxy, 0);	// Move to the bottom line of the window
	waddstr(debugWindow, str);					// Print the line
	waddstr(debugWindow, "\n");					// Carriage return to scroll the window up
}

/*
 * Draws the current state of the game, including the current district.
 */
void Game::UpdateUI() {
	pDistrict->draw(mapWindow);

	wrefresh(mapWindow);
	wrefresh(activityWindow);
}

/*
 * This method is called when the game is over.
 */
void Game::gameOver() {
	wmove(activityWindow, 0, 0);
	waddstr(activityWindow, "Game Over.");

	wrefresh(activityWindow);
}
