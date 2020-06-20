//============================================================================
// Name        : DISTRICTS.cpp
// Author      : Samuel Copping
// Version     :
// Copyright   : 
// Description : A procedurally generated base building game.
//============================================================================

#include "game/Constants.h"
#include <iostream>
#include "game/Game.h"
#include "ui/UI.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ws;

void startNewGame();
void quitMessage();

int main() {
	bool quit = false;
	bool invalidSelection;
	string inputText;

	do {
		UI::mainMenu();

		do {
			cin >> ws;					// Ignores leading whitespace
			getline(cin, inputText);	// Gets a line from the user

			invalidSelection = false;

			// Perform the action, or wait for more input if not valid
			if (inputText == "1")
				startNewGame();
			else if (inputText == "0") {
				quitMessage();
				quit = true;
			}
			else {
				UI::badMenuSelection();
				invalidSelection = true;
			}
		}
		while (invalidSelection);
	}
	while (!quit);

	return 0;
}

void startNewGame() {
	if (DEBUG)
		cout << "Starting a new game..." << endl;

	Game newGame;

	try {
		newGame.play();
	}
	catch (std::exception& ex) {
		cout << "Exception caught in main. Terminating game." << endl;
	}

	cout << endl << endl << endl;
}

void quitMessage() {
	cout << "Quitting..." << endl;
}
