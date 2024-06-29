#include <iostream>
#include "game/Game.hpp"
#include "ui/UI.hpp"
#include "ui/MainMenuSelections.hpp"
#include "helpers/Filesystem.hpp"
#include "logging/global.hpp"

void playNewGame();

int main(int argc, char *argv[])
{
	// Initialise the filesystem with the executable path
	if (argc > 0)
	{
		Filesystem::initialise(argv[0]);
	}

	glog_info("Program has started");

	// Initialise the UI, exit if it fails
	if (!UI::initialise())
	{
		std::cerr << "ERROR: DISTRICTS couldn't run because the UI could not initialise properly." << std::endl;
		return 1;
	}

	int returnCode = -1;
	while (returnCode == -1)
	{
		MainMenuSelection::MainMenuSelection selection = UI::mainMenu();
		glog_debug("Main menu selection: " + std::to_string(selection));

		switch (selection)
		{
		case MainMenuSelection::NewGame:
			playNewGame();
			break;
		case MainMenuSelection::Quit:
			returnCode = 0;
			break;
		default:
			returnCode = 1;
			break;
		}
	}

	UI::terminate();

	if (returnCode != 0)
	{
		std::cerr << "ERROR: DISTRICTS did not close correctly (return code " << returnCode << "). Please notify the developer!" << std::endl;
	}

	glog_info("Program is exiting");

	return returnCode;
}

void playNewGame()
{
	glog_info("Starting a new game");

	try
	{
		Game newGame;
		newGame.play();
	}
	catch (const std::exception &ex)
	{
		UI::showErrorScreen(ex);
	}

	glog_info("Game has ended, returning to main menu");
}
