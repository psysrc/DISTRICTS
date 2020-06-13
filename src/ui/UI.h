#ifndef SRC_UI_H_
#define SRC_UI_H_

#include "commands/PlayerCommand.h"
#include <memory>
#include <string>

class District;
class Tile;

namespace UI {

bool initialise();
void terminate();
void displayActivityMessage(const char* const str);
void displayActivityMessage(const std::string& str);
void displayDebugMessage(const char* const str);
void displayDebugMessage(const std::string& str);
void currentDistrict(std::shared_ptr<District> spDistrict);
void update();
void mainMenu();
void badMenuSelection();
void pause();
void unpause();
Cmds::PlayerCommand* getPlayerCommand();
Tile* selectTile(District*);
void rotatePlaySpinner();

}

#endif /* SRC_UI_H_ */
