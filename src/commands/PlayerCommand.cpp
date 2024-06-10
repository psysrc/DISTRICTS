#include <commands/PlayerCommand.h>

namespace Cmds
{

	PlayerCommand::PlayerCommand(std::string description) : description(description) {}

	PlayerCommand::~PlayerCommand() {}

	std::string PlayerCommand::getDescription() const
	{
		return description;
	}

} /* namespace Cmds */
