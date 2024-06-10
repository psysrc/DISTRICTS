#ifndef SRC_COMMANDS_BUILDBRIDGE_H_
#define SRC_COMMANDS_BUILDBRIDGE_H_

#include <commands/PlayerCommand.h>

class District;

namespace Cmds
{

	class BuildBridge : public PlayerCommand
	{
	public:
		BuildBridge();
		virtual ~BuildBridge();
		virtual void execute(District *) override;
	};

} /* namespace Cmds */

#endif /* SRC_COMMANDS_BUILDBRIDGE_H_ */
