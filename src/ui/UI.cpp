#include "UI.hpp"

#include <ncurses.h>
#include <unordered_map>
#include <iostream>
#include "game/TileCoordinates.hpp"
#include "game/District.hpp"
#include "commands/Quit.hpp"
#include "commands/PauseToggle.hpp"
#include "commands/CutDownTrees.hpp"
#include "commands/BuildBridge.hpp"
#include <sstream>
#include "components/RenderComponent.hpp"
#include <memory>
#include "TitleArt.hpp"
#include "game/VersionInfo.hpp"
#include <string>
#include <vector>
#include <sstream>
#include "ui/TileColours.hpp"
#include <thread>
#include <chrono>
#include "calendar/SettlersAgeCalendar.hpp"

namespace UI
{

	static WINDOW *districtWindow;
	static WINDOW *activityWindow;
	static WINDOW *headerWindow;
	static WINDOW *actionWindow;
	static std::weak_ptr<District> wpCurrentDistrict;
	static bool paused;
	static std::weak_ptr<SettlersAgeCalendar> calendar;

	typedef std::pair<char, Cmds::PlayerCommand *> KeyCommand;
	static std::unordered_map<char, Cmds::PlayerCommand *> commandKeyMap{
		KeyCommand('q', new Cmds::Quit),
		KeyCommand(' ', new Cmds::PauseToggle),
		KeyCommand('a', new Cmds::CutDownTrees),
		KeyCommand('b', new Cmds::BuildBridge)};

	void renderGridPosition(TileCoordinates coords, int colourPair, char symbol);
	static void clearAll();
	static void refresh();
	static void rotatePlaySpinner();

	/*
	 * Initialises the UI in the terminal ready for the game and the program as a whole.
	 * Returns whether the UI initialisation succeeded or not.
	 */
	bool initialise()
	{
		// Prepare the terminal window for ncurses-style output
		initscr();

		wclear(stdscr);
		wrefresh(stdscr);

		// Check that the terminal supports colours
		if (!has_colors())
		{
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
		init_pair(COLOUR_PLAINS, COLOR_WHITE, COLOR_GREEN);
		init_pair(COLOUR_WATER, COLOR_WHITE, COLOR_BLUE);
		init_pair(COLOUR_STONE, COLOR_BLACK, COLOR_WHITE);
		init_pair(COLOUR_HIGHLIGHTED, COLOR_WHITE, COLOR_RED);
		init_pair(COLOUR_BRIDGE, COLOR_BLACK, COLOR_YELLOW);

		// Define the windows in the terminal
		constexpr unsigned int headerWindowHeight = 4;

		// Parameters are: row count (height / y), column count (width / x), row origin, column origin
		districtWindow = newwin(District::districtSize, District::districtSize * 2, 0, 0);
		activityWindow = newwin(8, District::districtSize * 2, District::districtSize + 1, 0);
		headerWindow = newwin(headerWindowHeight, 32, 0, (District::districtSize * 2) + 2);
		actionWindow = newwin(District::districtSize - headerWindowHeight, 32, headerWindowHeight, (District::districtSize * 2) + 2);

		// Make the activity and debug windows automatically scroll up after writing to the bottom row
		scrollok(activityWindow, TRUE);

		curs_set(0);		  // Set the cursor to invisible
		noecho();			  // User-pressed keys are not output to the terminal
		cbreak();			  // No input buffer - a key press is immediately returned to the program
		keypad(stdscr, true); // Allows use of the arrow keys

		return true;
	}

	/*
	 * Terminates the UI when the program is being closed.
	 */
	void terminate()
	{
		clearAll();

		// Delete the windows that were in use
		delwin(districtWindow);
		delwin(activityWindow);
		delwin(headerWindow);
		delwin(actionWindow);

		endwin(); // End of ncurses activity
	}

	/*
	 * Clears all windows and refreshes them.
	 */
	static void clearAll()
	{
		wclear(districtWindow);
		wclear(activityWindow);
		wclear(headerWindow);
		wclear(actionWindow);

		refresh();
	}

	/**
	 * Prints a string to the Activity window.
	 */
	void displayActivityMessage(const std::string &str)
	{
		displayActivityMessage(str.c_str());
	}

	/**
	 * Prints a string to the Activity window.
	 */
	void displayActivityMessage(const char *str)
	{
		wmove(activityWindow, activityWindow->_maxy, 0); // Move to the bottom line of the window
		waddstr(activityWindow, str);					 // Print the line
		waddstr(activityWindow, "\n");					 // Carriage return to scroll the window up

		wrefresh(activityWindow);
	}

	/**
	 * Prints a string to the Debug window.
	 */
	void displayDebugMessage(const std::string &str)
	{
		displayDebugMessage(str.c_str());
	}

	/**
	 * Prints a string to the Debug window.
	 */
	void displayDebugMessage(const char *str)
	{
		displayActivityMessage(str);
	}

	/*
	 * Refreshes the UI with the most up-to-date information.
	 * Normally this isn't required because every operation which affects the UI automatically triggers an update of the required windows.
	 */
	static void refresh()
	{
		// Refresh all windows to the virtual screen
		wnoutrefresh(districtWindow);
		wnoutrefresh(activityWindow);
		wnoutrefresh(headerWindow);
		wnoutrefresh(actionWindow);

		// Refresh the physical screen from the virtual screen
		doupdate();
	}

	static void updateHeaderWindow()
	{
		wclear(headerWindow);

		auto spCurrentDistrict = wpCurrentDistrict.lock();

		std::string districtText;

		if (spCurrentDistrict)
		{
			districtText = "District " + spCurrentDistrict->getName();
		}
		else
		{
			districtText = "No district active";
		}

		std::string datetimeString;

		auto cal = calendar.lock();
		if (cal)
		{
			datetimeString = "Date: " + cal->to_string();
		}
		else
		{
			datetimeString = "No date information";
		}

		mvwaddstr(headerWindow, 0, 0, "--------------------------------");
		mvwaddstr(headerWindow, 1, 0, districtText.c_str());
		mvwaddstr(headerWindow, 2, 0, datetimeString.c_str());
		mvwaddstr(headerWindow, 3, 0, "--------------------------------");

		wrefresh(headerWindow);
	}

	/*
	 * Display and rotate the play spinner - only while the game is unpaused.
	 */
	static void rotatePlaySpinner()
	{
		if (paused)
			return;

		static int playSpinIndex = 0;
		static const char playSpinSprites[4] = {'\\', '|', '/', '-'};

		playSpinIndex++;

		if (playSpinIndex >= 4)
			playSpinIndex = 0;

		mvwaddch(actionWindow, 1, 15, playSpinSprites[playSpinIndex]);
		wrefresh(actionWindow);
	}

	/*
	 * Informs the UI of the new currently selected district and triggers a UI update.
	 * The UI will use this when updating to know which district to draw.
	 */
	void currentDistrict(std::shared_ptr<District> spDistrict)
	{
		wpCurrentDistrict = spDistrict;
		update();
	}

	/**
	 *
	 */
	void setCalendar(std::shared_ptr<SettlersAgeCalendar> cal)
	{
		calendar = cal;
		update();
	}

	/*
	 * Updates the UI with the latest information on the current district.
	 */
	void update()
	{
		updateHeaderWindow();

		rotatePlaySpinner();

		wrefresh(districtWindow);
	}

	/*
	 * Renders an entity at the provided grid position.
	 */
	void renderEntity(TileCoordinates coords, char symbol)
	{
		// Move the cursor to the correct position
		wmove(districtWindow, coords.y, coords.x * 2);

		// Draw the tile
		waddch(districtWindow, symbol);
		waddch(districtWindow, ' ');
	}

	/*
		Clear the district window without refreshing the screen.
	*/
	void renderEmptyDistrict()
	{
		werase(districtWindow);
	}

	/*
	 * Renders a tile at the provided grid position.
	 */
	void renderTile(TileCoordinates coords, int colourPair)
	{
		// Update the colours of this tile, keeping any entity symbols intact
		constexpr int numCharacters = 2;
		mvwchgat(districtWindow, coords.y, coords.x * 2, numCharacters, A_COLOR, colourPair, nullptr);
	}

	/*
	 * Renders an arbitrary grid position.
	 */
	void renderGridPosition(TileCoordinates coords, int colourPair, char symbol)
	{
		// Move the cursor to the correct position
		wmove(districtWindow, coords.y, coords.x * 2);

		// Draw the tile
		wattron(districtWindow, COLOR_PAIR(colourPair));
		waddch(districtWindow, symbol);
		waddch(districtWindow, ' ');
		wattroff(districtWindow, COLOR_PAIR(colourPair));
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
	MainMenuSelection::MainMenuSelection mainMenu()
	{
		wclear(stdscr);

		int windowX, windowY;

		getmaxyx(stdscr, windowY, windowX);							  // Get the current window size
		const int titleArtTopOffset = windowY / 10;					  // Gap size between the top of the window and the title art
		const int titleArtLeftOffset = (windowX - titleArtWidth) / 2; // Calculate offset from the left side, to centre the title art properly

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
			flushinp();			// Flush the input buffer
			char key = getch(); // Get the key from the player

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
		wclear(activityWindow); // Text may be left over in the activity window from previous games
		wrefresh(stdscr);

		return selection;
	}

	/*
	 * Updates the UI to display information to the player whilst the game is paused.
	 */
	void pause()
	{
		wclear(actionWindow);

		mvwaddstr(actionWindow, 1, 9, "- GAME PAUSED -");
		mvwaddstr(actionWindow, 2, 4, "Press <SPACE> to unpause");

		mvwaddstr(actionWindow, 5, 0, "Available commands:");
		mvwaddstr(actionWindow, 6, 0, "~~~~~~~~~~~~~~~~~~~");

		int y = 7;

		for (KeyCommand kc : commandKeyMap)
		{
			if (dynamic_cast<Cmds::PauseToggle *>(kc.second) != nullptr) // Skip the pause command
				continue;

			std::stringstream ss;
			ss << kc.first << " : " << kc.second->getDescription();

			mvwaddstr(actionWindow, y, 1, ss.str().c_str());

			y++;
		}

		wrefresh(actionWindow);

		paused = true;
	}

	/*
	 * Updates the UI to hide unnecessary information whilst the game is playing.
	 */
	void unpause()
	{
		wclear(actionWindow);

		mvwaddstr(actionWindow, 2, 5, "Press <SPACE> to pause");

		wrefresh(actionWindow);

		paused = false;
	}

	/**
	 * Checks input from the user while the game is running to see if the user wants to pause the game.
	 * This method will return instantly.
	 */
	bool letPlayerPause()
	{
		bool pause;

		timeout(0); // Briefly go to non-blocking input mode for getch()

		while (true)
		{
			// Continuously read the each key press from the input buffer
			// We want to know if they pressed the pause key at any point during this pause between game ticks
			char key = getch();

			if (key == ERR) // Check for a timeout, i.e. the input buffer is empty
			{
				pause = false;
				break;
			}
			else
			{
				// Find the pressed key in the command mappings
				auto found = commandKeyMap.find(key);

				// If the key corresponds to a command
				if (found != commandKeyMap.end())
				{
					// If the command pressed is the pause toggle
					if (dynamic_cast<Cmds::PauseToggle *>(found->second) != nullptr)
					{
						pause = true;
						break;
					}
				}
			}
		}

		timeout(-1); // Go back to blocking input mode

		return pause;
	}

	/*
	 * Wait for a command from the player.
	 */
	Cmds::PlayerCommand *getPlayerCommand()
	{
		// Flush input buffer first
		// This helps prevent issues when the user holds down or spams keys, which completely floods the input buffer
		flushinp();

		char key = getch(); // Get the key from the player

		if (key <= 90 && key >= 65) // If command is a capital letter (A-Z)
			key += 32;				// Change to its lowercase letter (a-z)

		auto found = commandKeyMap.find(key); // Find the pressed key in the command mappings

		if (found != commandKeyMap.end())
		{						  // If found
			return found->second; // Return the command
		}
		else
		{
			return nullptr; // Otherwise return nullptr
		}
	}

	/*
	 * Prompts the user to select a tile coordinate in the district.
	 */
	std::optional<TileCoordinates> selectTileCoordinates(District *)  // TODO: Remove paramter
	{
		displayDebugMessage("Please select a tile.");

		// Start in the middle
		TileCoordinates coords(District::districtSize / 2, District::districtSize / 2);

		bool returnTile = false;
		bool cancel = false;

		while (true)
		{
			// Remember the current tile data so we can render it back to the screen later
			chtype normalDisplay = mvwinch(districtWindow, coords.y, coords.x * 2);
			TileCoordinates previousCoords(coords);

			// Highlight the current grid position
			renderGridPosition(coords, COLOUR_HIGHLIGHTED, normalDisplay & A_CHARTEXT);

			wrefresh(districtWindow);

			// Get user input
			// They will either want to move the current highlighted tile, select it, or cancel this select operation
			int command = getch();

			switch (command)
			{
			case KEY_LEFT:
				if (coords.x > 0)
					coords.x--;
				break;
			case KEY_RIGHT:
				if (coords.x < District::districtSize - 1)
					coords.x++;
				break;
			case KEY_UP:
				if (coords.y > 0)
					coords.y--;
				break;
			case KEY_DOWN:
				if (coords.y < District::districtSize - 1)
					coords.y++;
				break;
			case '\n': // ENTER
				returnTile = true;
				break;
			case 'q':
				cancel = true;
				break;
			default:
				break;
			}

			// Revert previous grid position to normal
			renderGridPosition(previousCoords, PAIR_NUMBER(normalDisplay), normalDisplay & A_CHARTEXT);

			// Return tile or cancel if necessary
			if (returnTile)
			{
				wrefresh(districtWindow);
				return previousCoords;
			}
			else if (cancel)
			{
				wrefresh(districtWindow);
				return {};
			}
		}
	}

	void showErrorScreen(const std::exception &error)
	{
		wclear(stdscr);

		mvaddstr(1, 0, "Sorry, the game encountered a fatal error and had to be aborted.\nThe problem was:");
		mvaddstr(4, 0, error.what());
		wrefresh(stdscr);

		// Brief pause so the user doesn't accidentally close the error screen before they can read it
		std::this_thread::sleep_for(std::chrono::seconds(1));

		mvaddstr(10, 0, "Press any key to return to the main menu.");

		flushinp(); // Flush the input buffer
		getch();	// Get a key from the player
	}
}
