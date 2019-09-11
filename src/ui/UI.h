#ifndef SRC_UI_H_
#define SRC_UI_H_

#include <string>
#include <memory>
#include <ncurses.h>
#include "game/PlayerCommand.h"

class District;

class UI {
private:
	static WINDOW* mapWindow;
	static WINDOW* activityWindow;
	static WINDOW* debugWindow;
	static WINDOW* pauseWindow;
	static bool initialised;
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
	static void drawDistrict(std::unique_ptr<District>& upDistrict);
	static void refresh();
	static void mainMenu();
	static void badMenuSelection();
	static void pause(bool);
	static PlayerCommand getPlayerCommand();
};

#endif /* SRC_UI_H_ */
