//============================================================================
// Name        : DISTRICTS.cpp
// Author      : Samuel Copping
// Version     :
// Copyright   : 
// Description : A procedurally generated base building game.
//============================================================================

#include "Constants.h"
#include <iostream>
#include "Game.h"

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
		UserInterface::mainMenu();

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
				UserInterface::badMenuSelection();
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
	newGame.play();

	cout << endl << endl << endl;
}

void quitMessage() {
	cout << "Quitting..." << endl;
}
