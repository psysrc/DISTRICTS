#ifndef SRC_UI_H_
#define SRC_UI_H_

#include <string>
#include <memory>
#include <ncurses.h>
#include "game/PlayerCommand.h"

class District;
class Tile;

class UI {
private:
	static WINDOW* mapWindow;
	static WINDOW* activityWindow;
	static WINDOW* districtNameWindow;
	static WINDOW* promptWindow;
	static bool initialised;
	static std::string currentDistrict;
public:
	UI() = delete;
	~UI() = delete;
	static bool initialise();
	static void terminate();
	static void clearAll();
	static void displayActivityMessage(const char* const str);
	static void displayActivityMessage(const std::string str);
	static void displayDebugMessage(const std::string str);
	static void displayDebugMessage(const char* const str);
	static void districtName(const std::string);
	static void drawDistrict(std::unique_ptr<District>& upDistrict);
	static void drawTile(Tile*);
	static void drawGridPosition(int, int, int, char);
	static void refresh();
	static void mainMenu();
	static void badMenuSelection();
	static void pause();
	static void unpause();
	static PlayerCommand::PlayerCommand getPlayerCommand();
	static Tile* selectTile(District*);
};

#endif /* SRC_UI_H_ */
