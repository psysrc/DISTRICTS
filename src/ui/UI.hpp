#ifndef SRC_UI_H_
#define SRC_UI_H_

#include "commands/PlayerCommand.hpp"
#include <memory>
#include <string>
#include "ui/MainMenuSelections.hpp"
#include "game/TileCoordinates.hpp"
#include <optional>
#include "calendar/SettlersAgeCalendar.hpp"

class District;

namespace UI
{
    bool initialise();
    void terminate();
    void displayActivityMessage(const char *const str);
    void displayActivityMessage(const std::string &str);
    void displayDebugMessage(const char *const str);
    void displayDebugMessage(const std::string &str);
    void currentDistrict(std::shared_ptr<District> spDistrict);
    void update();
    MainMenuSelection::MainMenuSelection mainMenu();
    void pause();
    void unpause();
    bool letPlayerPause();
    Cmds::PlayerCommand *getPlayerCommand();
    std::optional<TileCoordinates> selectTileCoordinates(District *);
    void showErrorScreen(const std::exception& error);
    void renderTile(TileCoordinates, int colourPair);
	void renderEntity(TileCoordinates, char symbol);
    void renderEmptyDistrict();
    void setCalendar(std::shared_ptr<SettlersAgeCalendar>);
}

#endif /* SRC_UI_H_ */
