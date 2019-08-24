#ifndef SRC_USERINTERFACE_H_
#define SRC_USERINTERFACE_H_

#include <string>
#include <ncurses.h>
#include <iostream>
#include <memory>
#include "Constants.h"
#include "District.h"

class UserInterface {
private:
	static WINDOW* mapWindow;
	static WINDOW* activityWindow;
	static WINDOW* debugWindow;
public:
	UserInterface() = delete;
	~UserInterface() = delete;
	static bool initialise();
	static void terminate();
	static void displayActivityMessage(const char* const str);
	static void displayActivityMessage(const std::string str);
	static void displayDebugMessage(const std::string str);
	static void displayDebugMessage(const char* const str);
	static void drawDistrict(std::unique_ptr<District>& upDistrict);
	static void refresh();
};

#endif /* SRC_USERINTERFACE_H_ */
