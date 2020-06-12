#include "UI.h"

#include <ncurses.h>
#include <unordered_map>
#include <iostream>
#include "game/Constants.h"
#include "game/Tile.h"
#include "game/District.h"
#include "commands/Quit.h"
#include "commands/PauseToggle.h"
#include "commands/CutDownTrees.h"
#include "commands/BuildBridge.h"
#include <sstream>

namespace UI {

static WINDOW* mapWindow;
static WINDOW* activityWindow;
static WINDOW* districtNameWindow;
static WINDOW* promptWindow;
static bool initialised = false;
static std::string currentDistrict;
static int playSpinIndex = 0;

typedef std::pair<char, Cmds::PlayerCommand*> KeyCommand;
static std::unordered_map<char, Cmds::PlayerCommand*> commandKeyMap {
	KeyCommand('q', new Cmds::Quit),
	KeyCommand(' ', new Cmds::PauseToggle),
	KeyCommand('a', new Cmds::CutDownTrees),
	KeyCommand('b', new Cmds::BuildBridge)
};

// Private UI methods
static void drawGridPosition(int row, int column, int colourPair, char symbol);
static void drawTile(Tile* tile);
static void clearAll();
static void refresh();
static void districtName(const std::string& str);


using std::cout;
using std::endl;


/*
 * Initialises the UI in the terminal ready for a game to be displayed.
 * Returns whether the UI initialisation succeeded or not.
 */
bool initialise() {
	if (initialised)
		return true;

	// Prepare the terminal window for ncurses-style output
	initscr();

	wclear(stdscr);
	wrefresh(stdscr);

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
	// Parameters are: row count (height), column count (width), row origin, column origin
	mapWindow = newwin(DISTRICT_SIZE, DISTRICT_SIZE * 2, 0, 0);
	activityWindow = newwin(8, DISTRICT_SIZE * 2, DISTRICT_SIZE + 1, 0);
	districtNameWindow = newwin(3, 32, 0, (DISTRICT_SIZE * 2) + 2);
	promptWindow = newwin(DISTRICT_SIZE - 3, 32, 3, (DISTRICT_SIZE * 2) + 2);

	// Make the map text brighter and bolder
	wattron(mapWindow, A_BOLD);

	// Make the activity and debug windows automatically scroll up after writing to the bottom row
	scrollok(activityWindow, TRUE);

	curs_set(0);	// Set the cursor to invisible
	noecho();		// User-pressed keys are not output to the terminal
	cbreak();		// No input buffer - a key press is immediately returned to the program
	keypad(stdscr, true);	// Allows use of the arrow keys

	currentDistrict = "";

	initialised = true;

	return true;
}

/*
 * Terminates the UI when the game is being closed and the user is going back to the main menu.
 */
void terminate() {
	if (!initialised)
		return;

	clearAll();

	// Delete the windows that were in use
	delwin(mapWindow);
	delwin(activityWindow);
	delwin(districtNameWindow);
	delwin(promptWindow);

	endwin();	// End of ncurses activity

	initialised = false;
}

/*
 * Clears all windows and refreshes them.
 */
static void clearAll() {
	if (!initialised)
		return;

	wclear(mapWindow);
	wclear(activityWindow);
	wclear(districtNameWindow);
	wclear(promptWindow);

	refresh();
}

/**
 * Prints a string to the Activity window.
 */
void displayActivityMessage(const std::string& str) {
	displayActivityMessage(str.c_str());
}

/**
 * Prints a string to the Activity window.
 */
void displayActivityMessage(const char* str) {
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
void displayDebugMessage(const std::string& str) {
	displayDebugMessage(str.c_str());
}

/**
 * Prints a string to the Debug window.
 */
void displayDebugMessage(const char* str) {
	displayActivityMessage(str);
}

/*
 * Refreshes the UI with the most up-to-date information.
 * Normally this isn't required because every operation which affects the UI automatically triggers an update of the required windows.
 */
static void refresh() {
	if (!initialised)
		return;

	// Refresh all windows to the virtual screen
	wnoutrefresh(mapWindow);
	wnoutrefresh(activityWindow);
	wnoutrefresh(districtNameWindow);
	wnoutrefresh(promptWindow);

	// Refresh the physical screen from the virtual screen
	doupdate();
}

/*
 * Updates the UI with the name of the current district.
 */
static void districtName(const std::string& str) {
	if (!initialised || str == currentDistrict)
		return;

	currentDistrict = str;

	std::string text = "District " + str;

	mvwaddstr(districtNameWindow, 0, 0, "--------------------------------");
	mvwaddstr(districtNameWindow, 1, 0, text.c_str());
	mvwaddstr(districtNameWindow, 2, 0, "--------------------------------");

	wrefresh(districtNameWindow);
}

/*
 * Display and rotate the play spinner while the game is unpaused.
 */
void rotatePlaySpinner() {
	static const char playSpinSprites[4] = {'\\', '|', '/', '-'};

	playSpinIndex++;

	if (playSpinIndex >= 4)
		playSpinIndex = 0;

	mvwaddch(promptWindow, 1, 15, playSpinSprites[playSpinIndex]);
	wrefresh(promptWindow);
}

/*
 * Draws the given district to the UI and updates the current district name.
 */
void drawDistrict(std::unique_ptr<District>& upDistrict) {
	if (!initialised)
		return;

	districtName(upDistrict->getName());

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
static void drawTile(Tile* tile) {
	if (!initialised)
		return;

	drawGridPosition(tile->getX(), tile->getY(), tile->getDrawColour(), tile->getDrawSymbol());
}

/*
 * Draws a colour and symbol to a particular grid position.
 */
static void drawGridPosition(int row, int column, int colourPair, char symbol) {
	if (!initialised)
		return;

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
void mainMenu() {
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
void badMenuSelection() {
	if (initialised)
		return;

	cout << "Invalid selection. Please select an option from the menu above." << endl;
}

/*
 * Updates the UI to display information to the player whilst the game is paused.
 */
void pause() {
	if (!initialised)
		return;

	wclear(promptWindow);

	mvwaddstr(promptWindow, 1, 9, "- GAME PAUSED -");
	mvwaddstr(promptWindow, 2, 4, "Press <SPACE> to unpause");

	mvwaddstr(promptWindow, 5, 0, "Available commands:");
	mvwaddstr(promptWindow, 6, 0, "~~~~~~~~~~~~~~~~~~~");

	int row = 7;

	for (KeyCommand kc : commandKeyMap)
	{
		if (dynamic_cast<Cmds::PauseToggle*>(kc.second) != nullptr)	// Skip the pause command
			continue;

		std::stringstream ss;
		ss << kc.first << " : " << kc.second->getDescription();

		mvwaddstr(promptWindow, row, 1, ss.str().c_str());

		row++;
	}

	wrefresh(promptWindow);
}

/*
 * Updates the UI to hide unnecessary information whilst the game is playing.
 */
void unpause() {
	if (!initialised)
		return;

	wclear(promptWindow);

	mvwaddstr(promptWindow, 2, 5, "Press <SPACE> to pause");

	wrefresh(promptWindow);
}

/*
 * Wait for a command from the player.
 */
Cmds::PlayerCommand* getPlayerCommand() {
	if (!initialised)
		return nullptr;

	char key = getch();		// Get the key from the player

	if (key <= 90 && key >= 65)		// If command is a capital letter (A-Z)
		key += 32;					// Change to its lowercase letter (a-z)

	auto found = commandKeyMap.find(key);	// Find the pressed key in the command mappings

	if (found != commandKeyMap.end()) {		// If found
		return found->second;				// Return the command
	} else {
		return nullptr;						// Otherwise return nullptr
	}
}

/*
 * Prompts the user to select a tile in the district.
 */
Tile* selectTile(District* pDistrict) {
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

}
