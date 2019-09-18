#include "UI.h"

#include <iostream>
#include "game/Constants.h"
#include "game/Tile.h"
#include "game/District.h"
#include "ui/CommandMappings.h"

WINDOW* UI::mapWindow;
WINDOW* UI::activityWindow;
WINDOW* UI::debugWindow;
WINDOW* UI::pauseWindow;
bool UI::initialised = false;

using std::cout;
using std::endl;

/*
 * Initialises the UI in the terminal ready for a game to be displayed.
 * Returns whether the UI initialisation succeeded or not.
 */
bool UI::initialise() {
	if (initialised)
		return true;

	// Prepare the terminal window for ncurses-style output
	initscr();

	// Check that the terminal supports colours
	if (!has_colors()) {
		endwin();

		cout << "User Interface Error: Terminal does not support colours. Aborting." << endl;
		return false;
	}

	// Enable colour to be used in the terminal
	start_color();

	// Display default terminal colours for now
	use_default_colors();

	// Define colour pairs for the tiles
	init_pair(COLOUR_UNKNOWN, COLOR_RED, COLOR_BLACK);
	init_pair(COLOUR_PLAINS, COLOR_GREEN, COLOR_GREEN);
	init_pair(COLOUR_WATER, COLOR_BLUE, COLOR_BLUE);
	init_pair(COLOUR_STONE, COLOR_WHITE, COLOR_WHITE);
	init_pair(COLOUR_HIGHLIGHTED, COLOR_WHITE, COLOR_RED);
	init_pair(COLOUR_BRIDGE, COLOR_YELLOW, COLOR_YELLOW);

	// Define the windows in the terminal
	mapWindow = newwin(DISTRICT_SIZE, DISTRICT_SIZE * 2, 0, 0);
	activityWindow = newwin(8, DISTRICT_SIZE * 2, DISTRICT_SIZE + 1, 0);
	debugWindow = newwin(DISTRICT_SIZE, 30, 0, (DISTRICT_SIZE * 2) + 4);
	pauseWindow = newwin(8, 30, DISTRICT_SIZE + 1, (DISTRICT_SIZE * 2) + 4);

	// Make the map text brighter and bolder
	wattron(mapWindow, A_BOLD);

	// Make the activity and debug windows automatically scroll up after writing to the bottom row
	scrollok(activityWindow, TRUE);
	scrollok(debugWindow, TRUE);

	curs_set(0);	// Set the cursor to invisible
	noecho();		// User-pressed keys are not output to the terminal
	cbreak();		// No input buffer - a key press is immediately returned to the program
	keypad(stdscr, true);	// Allows use of the arrow keys

	UI::refresh();

	initialised = true;

	return true;
}

/*
 * Terminates the UI when the game is being closed and the user is going back to the main menu.
 */
void UI::terminate() {
	if (!initialised)
		return;

	clearAll();

	// Delete the windows that were in use
	delwin(mapWindow);
	delwin(activityWindow);
	delwin(debugWindow);
	delwin(pauseWindow);

	endwin();	// End of ncurses activity

	initialised = false;
}

/*
 * Clears all windows and refreshes them.
 */
void UI::clearAll() {
	if (!initialised)
		return;

	wclear(mapWindow);
	wclear(activityWindow);
	wclear(debugWindow);
	wclear(pauseWindow);

	refresh();
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
	if (initialised) {
		wmove(activityWindow, activityWindow->_maxy, 0);	// Move to the bottom line of the window
		waddstr(activityWindow, str);						// Print the line
		waddstr(activityWindow, "\n");						// Carriage return to scroll the window up

		wrefresh(activityWindow);
	}
	else {
		cout << "ACTIVITY: " << str << endl;
	}
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
	if (initialised) {
		wmove(debugWindow, debugWindow->_maxy, 0);	// Move to the bottom line of the window
		waddstr(debugWindow, str);					// Print the line
		waddstr(debugWindow, "\n");					// Carriage return to scroll the window up

		wrefresh(debugWindow);
	}
	else {
		cout << "DEBUG: " << str << endl;
	}
}

/*
 * Refreshes the UI with the most up-to-date information.
 * Normally this isn't required because every operation which affects the UI automatically triggers an update of the required windows.
 */
void UI::refresh() {
	if (!initialised)
		return;

	// Refresh all windows to the virtual screen
	wnoutrefresh(mapWindow);
	wnoutrefresh(activityWindow);
	wnoutrefresh(debugWindow);
	wnoutrefresh(pauseWindow);

	// Refresh the physical screen from the virtual screen
	doupdate();
}

/*
 * Draws the given district to the UI.
 */
void UI::drawDistrict(std::unique_ptr<District>& upDistrict) {
	if (!initialised)
		return;

	Tile** districtTiles = upDistrict->getTiles();

	// Draw the N*N grid of tiles
	for (int i = 0; i < DISTRICT_SIZE; i++) {
		for (int j = 0; j < DISTRICT_SIZE; j++) {
			drawTile(&districtTiles[i][j]);
		}
	}

	wrefresh(mapWindow);
}

/*
 * Draws a single tile to its correct position in the map window.
 */
void UI ::drawTile(Tile* tile) {
	drawGridPosition(tile->getX(), tile->getY(), tile->getDrawColour(), tile->getDrawSymbol());
}

/*
 * Draws a colour and symbol to a particular grid position.
 */
void UI::drawGridPosition(int row, int column, int colourPair, char symbol) {
	// Move the cursor to the correct position
	wmove(mapWindow, row, column * 2);

	// Draw the tile
	wattron(mapWindow, COLOR_PAIR(colourPair));
	waddch(mapWindow, symbol);
	waddch(mapWindow, ' ');
	wattroff(mapWindow, COLOR_PAIR(colourPair));
}

/*
 * Displays the main menu text.
 */
void UI::mainMenu() {
	if (initialised)
		return;

	cout << "Welcome to DISTRICTS." << endl << endl;

	cout << "Please select an option." << endl << endl;

	cout << "(1) New Game" << endl;
	cout << "(0) Quit" << endl << endl;
}

/*
 * Displays text that the user has not selected a valid option from the main menu.
 */
void UI::badMenuSelection() {
	if (initialised)
		return;

	cout << "Invalid selection. Please select an option from the menu above." << endl;
}

/*
 * Shows or hides the text indicating that the game is currently paused.
 */
void UI::pause(bool enable) {
	if (!initialised)
		return;

	if (enable) {
		mvwaddstr(pauseWindow, 1, 8, "-------------");
		mvwaddstr(pauseWindow, 2, 8, " GAME PAUSED ");
		mvwaddstr(pauseWindow, 3, 8, "-------------");
	}
	else {
		wclear(pauseWindow);
	}

	wrefresh(pauseWindow);
}

/*
 * Wait for a command from the player.
 */
PlayerCommand::PlayerCommand UI::getPlayerCommand() {
	char key = getch();

	if (key <= 90 && key >= 65)		// If command is a capital letter (A-Z)
		key += 32;					// Change to its lowercase letter (a-z)

	switch (key) {
	case CommandMappings::CommandMappings::PauseToggle:
		return PlayerCommand::PauseToggle;
	case CommandMappings::CommandMappings::Quit:
		return PlayerCommand::Quit;
	case CommandMappings::CommandMappings::CutDownTrees:
		return PlayerCommand::CutDownTrees;
	case CommandMappings::CommandMappings::BuildBridge:
		return PlayerCommand::BuildBridge;
	default:
		return PlayerCommand::NullCommand;
	}
}

/*
 * Prompts the user to select a tile in the district.
 */
Tile* UI::selectTile(District* pDistrict) {
	displayDebugMessage("Please select a tile.");

	// Start in the middle
	int row = DISTRICT_SIZE / 2;
	int column = DISTRICT_SIZE / 2;

	bool returnTile = false;
	bool cancel = false;

	while (true) {
		// Remember what this grid position looked like before we highlighted it
		Tile* currentTile = pDistrict->getTile(row, column);

		// Remember the tile so we can get its old colour back
		chtype normalDisplay = mvwinch(mapWindow, row, column * 2);

		// Highlight the current grid position
		drawGridPosition(row, column, COLOUR_HIGHLIGHTED, currentTile->getDrawSymbol());

		wrefresh(mapWindow);

		// Get user input
		// They will either want to move the current highlighted tile, select it, or cancel this select operation
		int command = getch();

		switch (command) {
		case KEY_LEFT:
			if (column > 0)
				column--;
			break;
		case KEY_RIGHT:
			if (column < DISTRICT_SIZE - 1)
				column++;
			break;
		case KEY_UP:
			if (row > 0)
				row--;
			break;
		case KEY_DOWN:
			if (row < DISTRICT_SIZE - 1)
				row++;
			break;
		case '\n':	// ENTER
			returnTile = true;
			break;
		case 'q':
			cancel = true;
			break;
		default:
			break;
		}

		// Revert previous grid position to normal
		drawGridPosition(currentTile->getX(), currentTile->getY(), PAIR_NUMBER(normalDisplay), currentTile->getDrawSymbol());

		// Return tile or cancel if necessary
		if (returnTile) {
			wrefresh(mapWindow);
			return currentTile;
		}
		else if (cancel) {
			wrefresh(mapWindow);
			return nullptr;
		}
	}
}

