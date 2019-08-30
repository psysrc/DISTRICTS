#include "UI.h"

WINDOW* UI::mapWindow;
WINDOW* UI::activityWindow;
WINDOW* UI::debugWindow;

using std::cout;
using std::endl;

/*
 * Initialises the UI in the terminal ready for a game to be displayed.
 * Returns whether the UI initialisation succeeded or not.
 */
bool UI::initialise() {
	// Prepare the terminal window for ncurses-style output
	initscr();

	// Check that the terminal supports colours
	if (!has_colors()) {
		endwin();

		std::cout << "User Interface Error: Terminal does not support colours. Aborting." << std::endl;
		return false;
	}

	// Enable colour to be used in the terminal
	start_color();

	// Display default terminal colours for now
	use_default_colors();

	// Define colour pairs for the tiles
	init_pair(COLOUR_CITIZEN, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOUR_PLAINS, COLOR_GREEN, COLOR_GREEN);
	init_pair(COLOUR_WATER, COLOR_BLUE, COLOR_BLUE);
	init_pair(COLOUR_STONE, COLOR_WHITE, COLOR_WHITE);
	init_pair(COLOUR_UNKNOWN, COLOR_RED, COLOR_BLACK);

	// Define the windows in the terminal
	mapWindow = newwin(DISTRICT_SIZE, DISTRICT_SIZE * 2, 0, 0);
	activityWindow = newwin(8, DISTRICT_SIZE * 2, DISTRICT_SIZE + 1, 0);
	debugWindow = newwin(DISTRICT_SIZE, 40, 0, (DISTRICT_SIZE * 2) + 4);

	// Make the map text brighter and bolder
	wattron(mapWindow, A_BOLD);

	// Make the activity and debug windows automatically scroll up after writing to the bottom row
	scrollok(activityWindow, TRUE);
	scrollok(debugWindow, TRUE);

	UI::refresh();

	return true;
}

/*
 * Terminates the UI when the game is being closed and the user is going back to the main menu.
 */
void UI::terminate() {
	// Delete the windows that were in use
	delwin(mapWindow);
	delwin(activityWindow);
	delwin(debugWindow);

	endwin();	// End of ncurses activity
}

/**
 * Prints a string to the Activity window.
 */
void UI::displayActivityMessage(const std::string str) {
	displayActivityMessage(str.c_str());
}

/**
 * Prints a string to the Activity window.
 */
void UI::displayActivityMessage(const char* str) {
	wmove(activityWindow, activityWindow->_maxy, 0);	// Move to the bottom line of the window
	waddstr(activityWindow, str);						// Print the line
	waddstr(activityWindow, "\n");						// Carriage return to scroll the window up

	wrefresh(activityWindow);
}

/**
 * Prints a string to the Debug window.
 */
void UI::displayDebugMessage(std::string str) {
	displayDebugMessage(str.c_str());
}

/**
 * Prints a string to the Debug window.
 */
void UI::displayDebugMessage(const char* str) {
	wmove(debugWindow, debugWindow->_maxy, 0);	// Move to the bottom line of the window
	waddstr(debugWindow, str);					// Print the line
	waddstr(debugWindow, "\n");					// Carriage return to scroll the window up

	wrefresh(debugWindow);
}

/*
 * Refreshes the UI with the most up-to-date information.
 * Normally this isn't required because every operation which affects the UI automatically triggers an update of the required windows.
 */
void UI::refresh() {
	wrefresh(mapWindow);
	wrefresh(activityWindow);
	wrefresh(debugWindow);
}

/*
 * Draws the given district to the UI.
 */
void UI::drawDistrict(std::unique_ptr<District>& upDistrict) {
	Tile** districtTiles = upDistrict->getTiles();

	wmove(mapWindow, 0, 0);	// Move the cursor to the window origin

	// Draw the N*N grid of tiles
	// The cursor will automatically wrap to the next line when it reaches the end of the window
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			int tileColour = districtTiles[i][j].getDrawColour();

			wattron(mapWindow, COLOR_PAIR(tileColour));
			waddch(mapWindow, districtTiles[i][j].getDrawSymbol());
			waddch(mapWindow, ' ');
			wattroff(mapWindow, COLOR_PAIR(tileColour));
		}
	}

	wrefresh(mapWindow);
}

/*
 * Displays the main menu text.
 */
void UI::mainMenu() {
	cout << "Welcome to DISTRICTS." << endl << endl;

	cout << "Please select an option." << endl << endl;

	cout << "(1) New Game" << endl;
	cout << "(0) Quit" << endl << endl;
}

void UI::badMenuSelection() {
	cout << "Invalid selection. Please select an option from the menu above." << endl;
}

