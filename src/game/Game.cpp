#include "Game.h"

#include <chrono>
#include "game/District.h"
#include "game/Constants.h"
#include "commands/PlayerCommand.h"
#include <iostream>
#include <thread>				// sleep_for(), std::thread
#include "ui/UI.h"
#include "commands/PauseToggle.h"
#include "commands/Quit.h"

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
 */
void Game::waitForPause() {
	Cmds::PlayerCommand* pCommand = nullptr;

	while(true) {
		pCommand = UI::getPlayerCommand();		// Wait for user to press a key

		if (dynamic_cast<Cmds::PauseToggle*>(pCommand) != nullptr) {
			break;	// Break from while loop when the command is pause toggle
		}
	}

	pause();	// Pause the game when the user presses the Pause key
}

/*
 * Defines the game loop while the game is still being played (game isn't over).
 */
void Game::play() {
	const milliseconds gameTick(250);	// Time per game tick
	milliseconds execStart;		// Time at the start of game tick
	milliseconds execEnd;		// Time at the end of game tick
	milliseconds execDuration;	// Duration of the game tick

	// execStart won't be calculated until the end of each pause, but each pause needs the execStart from the previous tick
	// It therefore needs initialising here before the game loop starts
	execStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	if (!UI::initialise()) {		// Initialise the UI and check if initialisation succeeded
		std::cout << "Could not load game due to a user interface error." << std::endl;
		return;						// Return if UI initialisation fails
	}

	UI::displayActivityMessage("Game started.");

	pause();	// Pause the game to start with

	UI::drawDistrict(upDistrict);	// Draw the district for the first time

	bool playerQuitting = false;

	// Game loop
	while (!gameIsOver && !playerQuitting) {
		// Get the time after game tick has been executed
		execEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		// Calculate the duration of the last execution
		execDuration = execEnd - execStart;

		// Sleep long enough so that the next game tick starts after the expected delay
		std::this_thread::sleep_for(gameTick - execDuration);

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
			UI::rotatePlaySpinner();
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
	Cmds::PlayerCommand* pCommand = nullptr;

	while (true) {
		pCommand = UI::getPlayerCommand();

		// First need to check if the user is quitting or unpausing
		// If so, exit the handle commands function with the appropriate return value
		if (dynamic_cast<Cmds::PauseToggle*>(pCommand) != nullptr)
			return false;
		else if (dynamic_cast<Cmds::Quit*>(pCommand) != nullptr)
			return true;
		else if (pCommand != nullptr)
			pCommand->execute(upDistrict.get());
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

	std::thread(&Game::waitForPause, this).detach();
}

/*
 * This method is called when the game is over.
 */
void Game::gameOver() const {
	UI::displayActivityMessage("Game Over.");

	std::this_thread::sleep_for(seconds(1));

	UI::terminate();
}
