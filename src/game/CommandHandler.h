#ifndef SRC_GAME_COMMANDHANDLER_H_
#define SRC_GAME_COMMANDHANDLER_H_

#include "PlayerCommand.h"

class Game;
class District;

class CommandHandler {
private:
	static District* pDistrict;
	static void cutDownTrees();
	static void buildBridge();
public:
	CommandHandler() = delete;
	~CommandHandler() = delete;
	static void handle(District*, PlayerCommand::PlayerCommand);
};

#endif /* SRC_GAME_COMMANDHANDLER_H_ */
