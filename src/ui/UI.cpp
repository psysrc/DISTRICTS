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
#include "components/PositionComponent.h"
#include "components/DrawComponent.h"
#include <memory>
#include "TitleArt.h"
#include "game/VersionInfo.h"
#include <string>
#include <vector>
#include <sstream>

namespace UI {

static WINDOW* mapWindow;
static WINDOW* activityWindow;
static WINDOW* districtNameWindow;
static WINDOW* promptWindow;
static std::weak_ptr<District> wpCurrentDistrict;
static bool paused;

typedef std::pair<char, Cmds::PlayerCommand*> KeyCommand;
static std::unordered_map<char, Cmds::PlayerCommand*> commandKeyMap {
	KeyCommand('q', new Cmds::Quit),
	KeyCommand(' ', new Cmds::PauseToggle),
	KeyCommand('a', new Cmds::CutDownTrees),
	KeyCommand('b', new Cmds::BuildBridge)
};

// Private UI methods
static void drawGridPosition(int row, int column, int colourPair, char symbol);
static void clearAll();
static void refresh();
static void updateDistrictName();
static void rotatePlaySpinner();


/*
 * Initialises the UI in the terminal ready for the game and the program as a whole.
 * Returns whether the UI initialisation succeeded or not.
 */
bool initialise() {
	// Prepare the terminal window for ncurses-style output
	initscr();

	wclear(stdscr);
	wrefresh(stdscr);

	// Check that the terminal supports colours
	if (!has_colors()) {
		endwin();

		std::cerr << "ERROR: DISTRICTS UI: Terminal does not support colours. Aborting." << std::endl;
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
	mapWindow = newwin(District::districtSize, District::districtSize * 2, 0, 0);
	activityWindow = newwin(8, District::districtSize * 2, District::districtSize + 1, 0);
	districtNameWindow = newwin(3, 32, 0, (District::districtSize * 2) + 2);
	promptWindow = newwin(District::districtSize - 3, 32, 3, (District::districtSize * 2) + 2);

	// Make the map text brighter and bolder
	wattron(mapWindow, A_BOLD);

	// Make the activity and debug windows automatically scroll up after writing to the bottom row
	scrollok(activityWindow, TRUE);

	curs_set(0);	// Set the cursor to invisible
	noecho();		// User-pressed keys are not output to the terminal
	cbreak();		// No input buffer - a key press is immediately returned to the program
	keypad(stdscr, true);	// Allows use of the arrow keys

	return true;
}

/*
 * Terminates the UI when the program is being closed.
 */
void terminate() {
	clearAll();

	// Delete the windows that were in use
	delwin(mapWindow);
	delwin(activityWindow);
	delwin(districtNameWindow);
	delwin(promptWindow);

	endwin();	// End of ncurses activity
}

/*
 * Clears all windows and refreshes them.
 */
static void clearAll() {
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
	wmove(activityWindow, activityWindow->_maxy, 0);	// Move to the bottom line of the window
	waddstr(activityWindow, str);						// Print the line
	waddstr(activityWindow, "\n");						// Carriage return to scroll the window up

	wrefresh(activityWindow);
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
static void updateDistrictName() {
	auto spCurrentDistrict = wpCurrentDistrict.lock();

	if (!spCurrentDistrict)
		return;

	std::string text = "District " + spCurrentDistrict->getName();

	mvwaddstr(districtNameWindow, 0, 0, "--------------------------------");
	mvwaddstr(districtNameWindow, 1, 0, text.c_str());
	mvwaddstr(districtNameWindow, 2, 0, "--------------------------------");

	wrefresh(districtNameWindow);
}

/*
 * Display and rotate the play spinner - only while the game is unpaused.
 */
static void rotatePlaySpinner() {
	if (paused)
		return;

	static int playSpinIndex = 0;
	static const char playSpinSprites[4] = {'\\', '|', '/', '-'};

	playSpinIndex++;

	if (playSpinIndex >= 4)
		playSpinIndex = 0;

	mvwaddch(promptWindow, 1, 15, playSpinSprites[playSpinIndex]);
	wrefresh(promptWindow);
}

/*
 * Informs the UI of the new currently selected district and triggers a UI update.
 * The UI will use this when updating to know which district to draw.
 */
void currentDistrict(std::shared_ptr<District> spDistrict) {
	wpCurrentDistrict = spDistrict;
	updateDistrictName();
	update();
}

/*
 * Updates the UI with the latest information on the current district
 */
void update() {
	auto spDistrict = wpCurrentDistrict.lock();
	
	if (!spDistrict)
	{
		displayDebugMessage("UI ERROR: Couldn't access current district for drawing");
		return;
	}

	const std::vector<std::vector<std::unique_ptr<Tile>>>& districtTiles = spDistrict->getTiles();

	// Draw the N*N grid of tiles
	for (int i = 0; i < District::districtSize; i++) {
		for (int j = 0; j < District::districtSize; j++) {
			Tile* tile = districtTiles[i][j].get();
			Entity* entity = tile->getEntity();
			drawGridPosition(i, j, tile->getDrawColour(), (entity == nullptr ? ' ' : entity->getComponent<DrawComponent>()->drawSymbol));
		}
	}

	rotatePlaySpinner();

	wrefresh(mapWindow);
}

/*
 * Draws a colour and symbol to a particular grid position.
 */
static void drawGridPosition(int row, int column, int colourPair, char symbol) {
	// Move the cursor to the correct position
	wmove(mapWindow, row, column * 2);

	// Draw the tile
	wattron(mapWindow, COLOR_PAIR(colourPair));
	waddch(mapWindow, symbol);
	waddch(mapWindow, ' ');
	wattroff(mapWindow, COLOR_PAIR(colourPair));
}

/*
 * Splits a string based on a provided delimiter.
 */
std::vector<std::string> splitString(std::string stringToSplit, char delimeter)
{
    std::stringstream ss(stringToSplit);
    std::string subString;
    std::vector<std::string> strings;

    while (std::getline(ss, subString, delimeter))
    {
       strings.push_back(subString);
    }

    return strings;
}

/*
 * Displays the main menu and returns the selected option.
 */
MainMenuSelection::MainMenuSelection mainMenu() {
	wclear(stdscr);

	int windowX, windowY;
	
	getmaxyx(stdscr, windowY, windowX);	// Get the current window size
	const int titleArtTopOffset = windowY / 10;	// Gap size between the top of the window and the title art
	const int titleArtLeftOffset = (windowX - titleArtWidth) / 2;	// Calculate offset from the left side, to centre the title art properly

	// Split the title art by each newline (\n), and print each line individually
	std::vector<std::string> titleArtLines = splitString(titleArt, '\n');
	for (unsigned short y = 0; y < titleArtLines.size(); y++)
	{
		mvaddstr(titleArtTopOffset + y, titleArtLeftOffset, titleArtLines[y].c_str());
	}

	std::string versionText = "Version: " + VersionInfo::versionString;
	mvaddstr(titleArtTopOffset + titleArtHeight + 1, titleArtLeftOffset, versionText.c_str());

	mvaddstr(titleArtTopOffset + titleArtHeight + 4, titleArtLeftOffset + 5, "(1) New Game");
	mvaddstr(titleArtTopOffset + titleArtHeight + 5, titleArtLeftOffset + 5, "(0) Quit");

	bool selected = false;
	MainMenuSelection::MainMenuSelection selection;
	while (!selected)
	{
		flushinp();				// Flush the input buffer
		char key = getch();		// Get the key from the player

		if (key == '1')
		{
			selection = MainMenuSelection::NewGame;
			selected = true;
		}
		else if (key == '0')
		{
			selection = MainMenuSelection::Quit;
			selected = true;
		}
	}

	wclear(stdscr);
	wrefresh(stdscr);

	return selection;
}

/*
 * Updates the UI to display information to the player whilst the game is paused.
 */
void pause() {
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

	paused = true;
}

/*
 * Updates the UI to hide unnecessary information whilst the game is playing.
 */
void unpause() {
	wclear(promptWindow);

	mvwaddstr(promptWindow, 2, 5, "Press <SPACE> to pause");

	wrefresh(promptWindow);

	paused = false;
}

/*
 * Wait for a command from the player.
 */
Cmds::PlayerCommand* getPlayerCommand() {
	// Flush input buffer first
	// This helps prevent issues when the user holds down or spams keys, which completely floods the input buffer
	flushinp();

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
	int row = District::districtSize / 2;
	int column = District::districtSize / 2;

	bool returnTile = false;
	bool cancel = false;

	char symbolToDraw = '?';

	while (true) {
		// Remember what this grid position looked like before we highlighted it
		Tile* currentTile = pDistrict->getTile(row, column);

		// Remember the tile so we can get its old colour back
		chtype normalDisplay = mvwinch(mapWindow, row, column * 2);

		// Highlight the current grid position
		if (currentTile->getEntity() && currentTile->getEntity()->getComponent<DrawComponent>())
			symbolToDraw = currentTile->getEntity()->getComponent<DrawComponent>()->drawSymbol;
		else
			symbolToDraw = ' ';
		
		drawGridPosition(row, column, COLOUR_HIGHLIGHTED, symbolToDraw);

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
			if (column < District::districtSize - 1)
				column++;
			break;
		case KEY_UP:
			if (row > 0)
				row--;
			break;
		case KEY_DOWN:
			if (row < District::districtSize - 1)
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
		if (currentTile->getEntity() && currentTile->getEntity()->getComponent<DrawComponent>())
			symbolToDraw = currentTile->getEntity()->getComponent<DrawComponent>()->drawSymbol;
		else
			symbolToDraw = ' ';

		drawGridPosition(currentTile->getCoordinates().x, currentTile->getCoordinates().y, PAIR_NUMBER(normalDisplay), symbolToDraw);

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
