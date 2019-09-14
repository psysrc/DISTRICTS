#ifndef SRC_GAME_COMMANDHANDLER_H_
#define SRC_GAME_COMMANDHANDLER_H_

#include "PlayerCommand.h"

class CommandHandler {
private:
	static void cutDownTrees();
public:
	CommandHandler() = delete;
	~CommandHandler() = delete;
	static void handle(PlayerCommand);
};

#endif /* SRC_GAME_COMMANDHANDLER_H_ */
