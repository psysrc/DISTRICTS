//============================================================================
// Name        : DISTRICTS.cpp
// Author      : Samuel Copping
// Version     :
// Copyright   : 
// Description : A procedurally generated base building game.
//============================================================================

#include <iostream>
#include <stdio.h>

using namespace std;

void startNewGame();
void loadGame();
void quit();

int main() {
	cout << "Welcome to DISTRICTS." << endl << endl << "Please select an option." << endl << endl;

	cout << "(1) New Game" << endl;
	cout << "(2) Load Game" << endl;
	cout << "(0) Quit" << endl << endl;

	bool invalidSelection;
	string inputText;

	do {
		cin >> ws;					// Ignores leading whitespace
		getline(cin, inputText);	// Gets a line from the user

		invalidSelection = false;

		// Perform the action, or wait for more input if not valid
		if (inputText == "1")
			startNewGame();
		else if (inputText == "2")
			loadGame();
		else if (inputText == "0") {
			quit();
		}
		else {
			cout << "Invalid selection. Please select an option from the menu above." << endl;
			invalidSelection = true;
		}
	}
	while (invalidSelection);

	return 0;
}

void startNewGame() {
	cout << "Starting a new game..." << endl;
}

void loadGame() {
	cout << "Loading a saved game..." << endl;
}

void quit() {
	cout << "Quitting..." << endl;
}
