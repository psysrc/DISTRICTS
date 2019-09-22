#include "Game.h"

#include <chrono>				// system_clock::
#include "game/District.h"
#include "game/Constants.h"
#include "game/PlayerCommand.h"
#include <iostream>
#include <thread>				// sleep_for(), pthread_*
#include "ui/UI.h"
#include "game/CommandHandler.h"

using namespace std::this_thread;
using namespace std::chrono;

Game::Game() {
	// Seed the random number generator with the current system time
	srand(system_clock::to_time_t(system_clock::now()));

	gameIsOver = false;
	gameIsPaused = false;

	upDistrict = std::make_unique<District>();

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

	PlayerCommand::PlayerCommand command = PlayerCommand::NullCommand;

	do {
		command = UI::getPlayerCommand();		// Wait for user to press a key
	}
	while (command != PlayerCommand::PauseToggle);

	pGame->pause();	// Pause the game when the user presses the Pause key

	return NULL;
}

/*
 * Defines the game loop while the game is still being played (game isn't over).
 */
void Game::play() {
	if (!UI::initialise()) {		// Initialise the UI and check if initialisation succeeded
		std::cout << "Could not load game due to a user interface error." << std::endl;
		return;						// Return if UI initialisation fails
	}

	unpause();	// Initialise the first thread to wait for the user pausing

	bool playerQuitting = false;

	const milliseconds gameTick(250);	// Time per game tick
	milliseconds execStart;		// Time at the start of game tick
	milliseconds execEnd;		// Time at the end of game tick
	milliseconds execDuration;	// Duration of the game tick

	// execStart won't be calculated until the end of each pause, but each pause needs the execStart from the previous tick
	// It therefore needs initialising here before the game loop starts
	execStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	// Game loop
	while (!gameIsOver && !playerQuitting) {
		// Get the time after game tick has been executed
		execEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		// Calculate the duration of the last execution
		execDuration = execEnd - execStart;

		// Sleep long enough so that the next game tick starts after the expected delay
		sleep_for(gameTick - execDuration);

		if (gameIsPaused) {
			// Get further user input (wait for it here)
			// If user wants to unpause, go ahead
			// If user wants to input several commands, process those commands as necessary
			// Wait here until the user unpauses

			playerQuitting = handleCommands();

			if (!playerQuitting)
				unpause();
		}

		// Get the time before the game tick is executed
		execStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		// Don't bother simulating the game if the user wants to quit
		if (!playerQuitting) {
			upDistrict->simulate();	// Simulate a game tick

			UI::drawDistrict(upDistrict);		// Draw the district
		}
	}

	gameOver();
}

/*
 * Handles the user inputting commands while the game is paused.
 * This method returns back to the game loop when the user wants to unpause the game or quit.
 * Returns whether or not the user wants to quit.
 */
bool Game::handleCommands() {
	PlayerCommand::PlayerCommand command = PlayerCommand::NullCommand;

	while (true) {
		command = UI::getPlayerCommand();

		if (command == PlayerCommand::PauseToggle)
			return false;	// Tell the game loop to unpause and continue
		else if (command == PlayerCommand::Quit)
			return true;	// Tell the game loop to quit
		else
			CommandHandler::handle(upDistrict.get(), command);
	}
}

/*
 * Tells the Game to pause so the user can input commands.
 * Simply activates a variable to tell the game loop to wait before proceeding.
 */
void Game::pause() {
	gameIsPaused = true;

	UI::pause();
}

/*
 * Called by the Game when the user wants to resume.
 * Creates a new thread to wait for user input again when they want to pause next time.
 */
void Game::unpause() {
	gameIsPaused = false;

	UI::unpause();

	// Set the thread's attribute to be detached
	pthread_attr_t pauseThreadAttr;
	pthread_attr_init(&pauseThreadAttr);
	pthread_attr_setdetachstate(&pauseThreadAttr, PTHREAD_CREATE_DETACHED);

	// Create the thread
	upPauseThread = std::make_unique<pthread_t>();
	pthread_create(upPauseThread.get(), &pauseThreadAttr, waitForPause, (void*) this);

	// Destroy attribute resources
	pthread_attr_destroy(&pauseThreadAttr);
}

/*
 * This method is called when the game is over.
 */
void Game::gameOver() const {
	UI::displayActivityMessage("Game Over.");

	sleep_for(seconds(1));

	UI::terminate();
}
