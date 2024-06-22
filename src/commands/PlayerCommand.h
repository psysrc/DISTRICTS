#ifndef SRC_COMMANDS_PLAYERCOMMAND_H_
#define SRC_COMMANDS_PLAYERCOMMAND_H_

#include <string>

class District;

namespace Cmds
{
	// Abstract class representing a command that the player can execute to the game.
	class PlayerCommand
	{
	public:
		PlayerCommand(std::string);
		virtual ~PlayerCommand();
		virtual void execute(District *) = 0;
		std::string getDescription() const;

	private:
		std::string description;
	};

} /* namespace Cmds */

#endif /* SRC_COMMANDS_PLAYERCOMMAND_H_ */
