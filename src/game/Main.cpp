#include "game/Constants.h"
#include <iostream>
#include "game/Game.h"
#include "ui/UI.h"
#include "ui/MainMenuSelections.h"

void playNewGame();

int main()
{
	// Initialise the UI, exit if it fails
	if (!UI::initialise())
	{
		std::cerr << "Failed to load DISTRICTS because the UI could not initialise properly. Terminating." << std::endl;
		return 1;
	}

	while (true)
	{
		MainMenuSelection::MainMenuSelection selection = UI::mainMenu();

		switch (selection)
		{
			case MainMenuSelection::NewGame:
				playNewGame();
				break;
			case MainMenuSelection::Quit:
				UI::terminate();
				return 0;
			default:
				UI::terminate();
				std::cerr << "Unknown main menu selection (" << selection << "). Terminating." << std::endl;
		}
	}
}

void playNewGame()
{
	Game newGame;

	try {
		newGame.play();
	}
	catch (std::exception& ex) {
		std::cerr << "Exception caught in main: " << ex.what() << ". Terminating." << std::endl;
	}
}
