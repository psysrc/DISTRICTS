#include "Game.h"

using std::cout;
using std::endl;
using namespace std::this_thread;
using namespace std::chrono;

Game::Game() {
	gameIsOver = false;
	gameIsPaused = false;

	pDistrict = std::make_shared<District>();

	if (DEBUG)
		cout << "New game created." << endl;

	initscr();	// Prepare the terminal window for Ncurses-style output

	// Define the windows in the terminal
	mapWindow = newwin(DISTRICT_SIZE, DISTRICT_SIZE * 2, 0, 0);
	activityWindow = newwin(10, DISTRICT_SIZE * 2, DISTRICT_SIZE + 2, 0);
	debugWindow = newwin(DISTRICT_SIZE, 40, 0, (DISTRICT_SIZE * 2) + 4);

	scrollok(activityWindow, TRUE);
	scrollok(debugWindow, TRUE);
}

Game::~Game() {
	delwin(mapWindow);
	delwin(activityWindow);
	delwin(debugWindow);
}

/*
 * This method runs in a separate thread to detect the user pausing the game.
 *
 */
void* waitForPause(void* args) {
	Game* pGame = (Game*) args;

	noecho();
	cbreak();

	getch();	// Wait for user to press a key

	pGame->pause();	// Pause the game when the user presses a key

	return NULL;
}

/*
 * Defines the game loop while the game is still being played (game isn't over).
 */
void Game::play() {
	unpause();	// Initialise the first thread to wait for the user pausing

	// Game loop
	while (!gameIsOver) {
		sleep_for(milliseconds(250));	// Wait for 1/4 of a second

		if (gameIsPaused) {
			// Get further user input (wait for it here)
			// If user wants to unpause, go ahead
			// If user wants to input several commands, process those commands as necessary
			// Wait here until the user unpauses

			handleCommands();

			unpause();
		}

		if (DEBUG)
			displayDebugMessage("Simulating district " + pDistrict->getName());

		pDistrict->simulate();	// Simulate a game tick

		// Render the game state to the user
		updateUI();
	}

	gameOver();
}

/*
 * Handles the user inputting commands while the game is paused.
 * This method returns back to the game loop when the user wants to unpause the game.
 */
void Game::handleCommands() {
	int command = -1;

	command = getch();

	switch (command) {
	case 'q':
		gameIsOver = true;
		break;
	case 'a':
		displayActivityMessage("A house has been constructed.");
		break;
	default:
		displayActivityMessage("Oh dear.");
	}
}

/*
 * Tells the Game to pause so the user can input commands.
 * Simply activates a variable to tell the game loop to wait before proceeding.
 */
void Game::pause() {
	gameIsPaused = true;
}

/*
 * Called by the Game when the user wants to resume.
 * Creates a new thread to wait for user input again when they want to pause next time.
 */
void Game::unpause() {
	gameIsPaused = false;

	pthread_t pauseThread;

	pthread_create(&pauseThread, NULL, waitForPause, (void*) this);
}

/**
 * Prints a string to the Activity window.
 */
void Game::displayActivityMessage(const char* str) {
	wmove(activityWindow, activityWindow->_maxy, 0);	// Move to the bottom line of the window
	waddstr(activityWindow, str);						// Print the line
	waddstr(activityWindow, "\n");						// Carriage return to scroll the window up
}

void Game::displayDebugMessage(std::string str) {
	displayDebugMessage(str.c_str());
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
void Game::updateUI() {
	pDistrict->draw(mapWindow);

	wrefresh(mapWindow);
	wrefresh(activityWindow);
	wrefresh(debugWindow);
}

/*
 * This method is called when the game is over.
 */
void Game::gameOver() {
	wmove(activityWindow, 0, 0);
	waddstr(activityWindow, "Game Over.");

	wrefresh(activityWindow);

	sleep_for(seconds(1));

	endwin();	// End of Ncurses activity
}
