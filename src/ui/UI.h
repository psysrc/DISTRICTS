#ifndef SRC_UI_H_
#define SRC_UI_H_

#include "commands/PlayerCommand.h"
#include <memory>
#include <string>
#include "ui/MainMenuSelections.h"

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
MainMenuSelection::MainMenuSelection mainMenu();
void pause();
void unpause();
bool letPlayerPause();
Cmds::PlayerCommand* getPlayerCommand();
Tile* selectTile(District*);

}

#endif /* SRC_UI_H_ */
