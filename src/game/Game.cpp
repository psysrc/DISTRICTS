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
#include "gamesystems/GrowSystem.h"
#include "gamesystems/WalkSystem.h"
#include "gamesystems/WorkSystem.h"
#include "gamesystems/CitizenSystem.h"
#include "gamesystems/MoveSystem.h"

using namespace std::chrono;

Game::Game() {
	// Seed the random number generator with the current system time
	srand(system_clock::to_time_t(system_clock::now()));

	gameIsOver = false;
	gameIsPaused = false;

	spDistrict = std::make_shared<District>();

	gameSystems.push_back(std::make_unique<WalkSystem>());
	gameSystems.push_back(std::make_unique<GrowSystem>());
	gameSystems.push_back(std::make_unique<WorkSystem>());
	gameSystems.push_back(std::make_unique<CitizenSystem>());
	gameSystems.push_back(std::make_unique<MoveSystem>());
}

Game::~Game() {

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

	UI::displayActivityMessage("Game started.");

	UI::unpause();	// Unpause the game to start with

	// Execute District::update() and MoveSystem::run() as soon as the game is started
	// This is required to initially update all PositionComponents' currentCoordinates
	// Otherwise the first tick of the game will show no entities, and suddenly they'll pop into existence
	spDistrict->update();
	gameSystems[4]->run(spDistrict.get());

	UI::currentDistrict(spDistrict);	// Set the current district and update

	// Game loop
	while (!gameIsOver) {
		// Get the time after game tick has been executed
		execEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		// Calculate the duration of the last execution
		execDuration = execEnd - execStart;
		
		// Sleep for just long enough so that the next game tick occurs precisely 'gameTick' milliseconds after the previous
		// This is so that even if one tick takes particularly long to process, the game runs at a steady pace
		std::this_thread::sleep_for(gameTick - execDuration);

		// Let the player pause for a short while before running the next game tick
		// We only delay long enough to ensure the time between ticks is exactly 'gameTick' milliseconds long
		if (UI::letPlayerPause()) {
			UI::pause();

			// Handle all commands from the player while the game is paused
			// The player will either quit the game or just unpause the game at this point
			bool playerQuitting = handleCommands();

			if (!playerQuitting)
				UI::unpause();
			else
				break;	// Exit the game loop when the player wants to quit
		}

		// Get the time before the game tick is executed
		execStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		for (std::unique_ptr<GameSystem>& system : gameSystems)
		{
			system->run(spDistrict.get());	// Run each gamesystem on the district
		}

		spDistrict->update();	// Update the district

		UI::update();	// Update the UI
	}

	gameOver();
}

/*
 * Handles the player inputting commands while the game is paused.
 * This method returns back to the game loop when the player wants to unpause the game or quit.
 * Returns whether or not the player wants to quit.
 */
bool Game::handleCommands() {
	Cmds::PlayerCommand* pCommand = nullptr;

	while (true) {
		pCommand = UI::getPlayerCommand();

		// First need to check if the player is quitting or unpausing
		// If so, exit the handle commands function with the appropriate return value
		if (dynamic_cast<Cmds::PauseToggle*>(pCommand) != nullptr)
		{
			return false;
		}
		else if (dynamic_cast<Cmds::Quit*>(pCommand) != nullptr)
		{
			// Confirm if the player wants to quit before quitting
			UI::displayActivityMessage("Are you sure you want to quit? Press quit again to confirm, or press pause to cancel.");

			while (true)
			{
				pCommand = UI::getPlayerCommand();

				if (dynamic_cast<Cmds::Quit*>(pCommand) != nullptr)
				{
					// Quit
					return true;
				}
				else if (dynamic_cast<Cmds::PauseToggle*>(pCommand) != nullptr)
				{
					// Inform the player they cancelled their quit command
					UI::displayActivityMessage("Cancelled quitting.");
					break;
				}
			}
		}
		else if (pCommand != nullptr)
		{
			// If it's any other ordinary command then execute it
			pCommand->execute(spDistrict.get());
		}
	}
}

/*
 * This method is called when the game is over.
 */
void Game::gameOver() const {
	UI::displayActivityMessage("Game Over.");
	UI::displayActivityMessage("You may quit the game when you are ready.");

	Cmds::PlayerCommand* pCommand;

	do
	{
		pCommand = UI::getPlayerCommand();
	}
	while (dynamic_cast<Cmds::Quit*>(pCommand) == nullptr);
}
