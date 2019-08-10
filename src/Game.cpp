#include "Game.h"

using std::cout;
using std::endl;
using namespace std::this_thread;
using namespace std::chrono;

Game::Game() {
	// Seed the random number generator with the current system time
	srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

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

	int keyPress = PlayerCommand::NullCmd;

	do {
		keyPress = getch();		// Wait for user to press a key
	}
	while (keyPress != PlayerCommand::Pause);

	pGame->pause();	// Pause the game when the user presses the Pause key

	return NULL;
}

/*
 * Defines the game loop while the game is still being played (game isn't over).
 */
void Game::play() {
	unpause();	// Initialise the first thread to wait for the user pausing

	int cmdState = 0;

	// Game loop
	while (!gameIsOver && cmdState != -1) {
		sleep_for(milliseconds(250));	// Wait for 1/4 of a second

		if (gameIsPaused) {
			// Get further user input (wait for it here)
			// If user wants to unpause, go ahead
			// If user wants to input several commands, process those commands as necessary
			// Wait here until the user unpauses

			cmdState = handleCommands();

			if (cmdState != -1)
				unpause();
		}

		// Don't bother running the following code if the user wants to quit (cmdState == -1)
		if (cmdState == 0) {
			if (DEBUG)
				displayDebugMessage("Simulating district " + pDistrict->getName());

			pDistrict->simulate();	// Simulate a game tick

			// Render the game state to the user
			updateUI();
		}
	}

	gameOver();
}

/*
 * Handles the user inputting commands while the game is paused.
 * This method returns back to the game loop when the user wants to unpause the game or quit.
 * Returns either 0 or -1 depending if the user wants to quit (-1 for quit, 0 to return to game).
 */
int Game::handleCommands() {
	int command = PlayerCommand::NullCmd;

	do {
		command = getch();

		if (command <= 90 && command >= 65)	// If command is a capital letter (A-Z)
			command += 32;					// Change to its lowercase letter (a-z)

		switch (command) {
		case PlayerCommand::Unpause:
			break;
		case PlayerCommand::Quit:
			return -1;	// Tell the game loop to quit
		case PlayerCommand::BuildHouse:
			displayActivityMessage("A house has been constructed.");
			break;
		}
	}
	while(command != PlayerCommand::Unpause);

	return 0;	// Tell the game loop to unpause and continue
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

	pPauseThread = std::make_unique<pthread_t>();

	pthread_create(pPauseThread.get(), NULL, waitForPause, (void*) this);
}

/**
 * Prints a string to the Activity window.
 */
void Game::displayActivityMessage(const char* str) const {
	wmove(activityWindow, activityWindow->_maxy, 0);	// Move to the bottom line of the window
	waddstr(activityWindow, str);						// Print the line
	waddstr(activityWindow, "\n");						// Carriage return to scroll the window up

	wrefresh(activityWindow);
}

void Game::displayDebugMessage(std::string str) const {
	displayDebugMessage(str.c_str());
}

/**
 * Prints a string to the Debug window.
 */
void Game::displayDebugMessage(const char* str) const {
	wmove(debugWindow, debugWindow->_maxy, 0);	// Move to the bottom line of the window
	waddstr(debugWindow, str);					// Print the line
	waddstr(debugWindow, "\n");					// Carriage return to scroll the window up

	wrefresh(debugWindow);
}

/*
 * Draws the current state of the game, including the current district.
 */
void Game::updateUI() const {
	pDistrict->draw(mapWindow);

	wrefresh(mapWindow);
	wrefresh(activityWindow);
	wrefresh(debugWindow);
}

/*
 * This method is called when the game is over.
 */
void Game::gameOver() const {
	displayActivityMessage("Game Over.");

	sleep_for(seconds(1));

	endwin();	// End of Ncurses activity
}
