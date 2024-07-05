#include "Game.hpp"

#include <chrono>
#include "game/District.hpp"
#include "commands/PlayerCommand.hpp"
#include <iostream>
#include <thread> // sleep_for(), std::thread
#include "ui/UI.hpp"
#include "commands/PauseToggle.hpp"
#include "commands/Quit.hpp"
#include "gamesystems/GrowSystem.hpp"
#include "gamesystems/WorkSystem.hpp"
#include "gamesystems/CitizenSystem.hpp"
#include "gamesystems/MoveSystem.hpp"
#include "gamesystems/WanderSystem.hpp"
#include "game/TickSpeed.hpp"
#include "components/CitizenComponent.hpp"
#include "components/NameComponent.hpp"
#include "gamesystems/RenderSystem.hpp"
#include "logging/global.hpp"

using namespace std::chrono;

Game::Game() : Game(system_clock::to_time_t(system_clock::now())) {}

Game::Game(unsigned int seed)
{
	glog_debug("Initialising new game");

	glog_info("Game seed: " + std::to_string(seed));
	srand(seed);

	gameIsOver = false;
	gameIsPaused = false;

	spDistrict = std::make_shared<District>();

	preUpdateGameSystems.push_back(std::make_unique<GrowSystem>());
	preUpdateGameSystems.push_back(std::make_unique<WorkSystem>());
	preUpdateGameSystems.push_back(std::make_unique<CitizenSystem>());
	preUpdateGameSystems.push_back(std::make_unique<WanderSystem>());
	preUpdateGameSystems.push_back(std::make_unique<MoveSystem>());

	postUpdateGameSystems.push_back(std::make_unique<RenderSystem>());

	calendar = SettlersAgeCalendar();
}

Game::~Game()
{
	glog_debug("Unloading game");
}

/*
 * Defines the game loop while the game is still being played (game isn't over).
 */
void Game::play()
{
	const milliseconds gameTick(1000 / ticksPerSecond); // Time per game tick
	milliseconds execStart;								// Time at the start of game tick
	milliseconds execEnd;								// Time at the end of game tick
	milliseconds execDuration;							// Duration of the game tick

	// execStart won't be calculated until the end of each pause, but each pause needs the execStart from the previous tick
	// It therefore needs initialising here before the game loop starts
	execStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	UI::unpause(); // Unpause the game to start with

	// Execute District::update() and post-update gamesystems as soon as the game is started
	// Otherwise the first tick of the game will show no entities or district, then suddenly they'll pop into existence
	spDistrict->update();
	for (std::unique_ptr<GameSystem> &system : postUpdateGameSystems)
		system->run(spDistrict.get());

	UI::currentDistrict(spDistrict); // Set the current district and update

	// Get the name of the first citizen in the district
	std::string citizenName = "<unknown>";
	for (const auto &entity : spDistrict->getEntities())
	{
		if (entity->hasComponent<CitizenComponent>())
		{
			citizenName = entity->getComponent<NameComponent>()->name;
			break;
		}
	}

	UI::displayActivityMessage("The first settler has arrived. Their name is '" + citizenName + "'.");
	UI::displayActivityMessage("They decide to name this district '" + spDistrict->getName() + "'.");

	// Game loop
	while (!gameIsOver)
	{
		// Get the time after game tick has been executed
		execEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		// Calculate the duration of the last execution
		execDuration = execEnd - execStart;

		// Sleep for just long enough so that the next game tick occurs precisely 'gameTick' milliseconds after the previous
		// This is so that even if one tick takes particularly long to process, the game runs at a steady pace
		std::this_thread::sleep_for(gameTick - execDuration);

		// Let the player pause for a short while before running the next game tick
		// We only delay long enough to ensure the time between ticks is exactly 'gameTick' milliseconds long
		if (UI::letPlayerPause())
		{
			UI::pause();

			// Handle all commands from the player while the game is paused
			// The player will either quit the game or just unpause the game at this point
			bool playerQuitting = handleCommands();

			if (!playerQuitting)
				UI::unpause();
			else
				return; // Completely exit the play() method when quitting
		}

		// Get the time before the game tick is executed
		execStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		runPreUpdateGameSystems();

		spDistrict->update(); // Update the district

		runPostUpdateGameSystems();

		calendar.advance();
		UI::displayDebugMessage(std::to_string(calendar.to_usat()));

		// Update the UI
		UI::update();
	}

	gameOver();
}

void Game::runPreUpdateGameSystems()
{
	for (std::unique_ptr<GameSystem> &system : preUpdateGameSystems)
	{
		system->run(spDistrict.get());
	}
}

void Game::runPostUpdateGameSystems()
{
	for (std::unique_ptr<GameSystem> &system : postUpdateGameSystems)
	{
		system->run(spDistrict.get());
	}
}

/*
 * Handles the player inputting commands while the game is paused.
 * This method returns back to the game loop when the player wants to unpause the game or quit.
 * Returns whether or not the player wants to quit.
 */
bool Game::handleCommands()
{
	Cmds::PlayerCommand *pCommand = nullptr;

	while (true)
	{
		pCommand = UI::getPlayerCommand();

		// First need to check if the player is quitting or unpausing
		// If so, exit the handle commands function with the appropriate return value
		if (dynamic_cast<Cmds::PauseToggle *>(pCommand) != nullptr)
		{
			return false;
		}
		else if (dynamic_cast<Cmds::Quit *>(pCommand) != nullptr)
		{
			// Confirm if the player wants to quit before quitting
			UI::displayActivityMessage("Are you sure you want to quit? Press quit again to confirm, or press pause to cancel.");

			while (true)
			{
				pCommand = UI::getPlayerCommand();

				if (dynamic_cast<Cmds::Quit *>(pCommand) != nullptr)
				{
					// Quit
					return true;
				}
				else if (dynamic_cast<Cmds::PauseToggle *>(pCommand) != nullptr)
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
void Game::gameOver() const
{
	UI::displayActivityMessage("Game Over.");
	UI::displayActivityMessage("You may quit the game when you are ready.");

	Cmds::PlayerCommand *pCommand;

	do
	{
		pCommand = UI::getPlayerCommand();
	} while (dynamic_cast<Cmds::Quit *>(pCommand) == nullptr);
}
