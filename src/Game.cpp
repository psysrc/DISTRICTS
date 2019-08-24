#include "Game.h"

using namespace std::this_thread;
using namespace std::chrono;

Game::Game() {
	// Seed the random number generator with the current system time
	srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

	gameIsOver = false;
	gameIsPaused = false;

	pDistrict = std::make_shared<District>();

	if (DEBUG)
		std::cout << "New game created." << std::endl;
}

Game::~Game() {

}

/*
 * This method runs in a separate thread to detect the user pausing the game.
 *
 */
void* waitForPause(void* args) {
	Game* pGame = static_cast<Game*>(args);

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
	if (!UserInterface::initialise()) {		// Initialise the UI and check if initialisation succeeded
		std::cout << "Could not load game due to a user interface error." << std::endl;
		return;								// Return if UI initialisation fails
	}

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
				UserInterface::displayDebugMessage("Simulating district " + pDistrict->getName());

			pDistrict->simulate();	// Simulate a game tick

			UserInterface::drawDistrict(pDistrict);		// Draw the district
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
			UserInterface::displayActivityMessage("A house has been constructed.");
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

/*
 * This method is called when the game is over.
 */
void Game::gameOver() const {
	UserInterface::displayActivityMessage("Game Over.");

	sleep_for(seconds(1));

	UserInterface::terminate();
}
