#include <iostream>
#include "game/Game.h"
#include "ui/UI.h"
#include "ui/MainMenuSelections.h"
#include "helpers/Filesystem.h"

void playNewGame();

int main(int argc, char *argv[])
{
	// Initialise the filesystem with the executable path
	if (argc > 0)
	{
		Filesystem::initialise(argv[0]);
	}

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

	return returnCode;
}

void playNewGame()
{
	Game newGame;

	try
	{
		newGame.play();
	}
	catch (std::exception &ex)
	{
		std::cerr << "Exception caught in main: " << ex.what() << ". Terminating." << std::endl;
	}
}
