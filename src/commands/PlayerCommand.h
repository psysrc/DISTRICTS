#ifndef SRC_COMMANDS_PLAYERCOMMAND_H_
#define SRC_COMMANDS_PLAYERCOMMAND_H_

#include <string>

class District;

namespace Cmds {

// Abstract class representing a command that the player can execute to the game.
class PlayerCommand {
private:
	std::string description;
public:
	PlayerCommand(std::string);
	virtual ~PlayerCommand();
	virtual void execute(District*) = 0;
	std::string getDescription() const;
};

} /* namespace Cmds */

#endif /* SRC_COMMANDS_PLAYERCOMMAND_H_ */
