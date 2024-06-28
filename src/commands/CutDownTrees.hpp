#ifndef SRC_COMMANDS_CUTDOWNTREES_H_
#define SRC_COMMANDS_CUTDOWNTREES_H_

#include "commands/PlayerCommand.hpp"

class District;

namespace Cmds
{

	class CutDownTrees : public PlayerCommand
	{
	public:
		CutDownTrees();
		virtual ~CutDownTrees();
		virtual void execute(District *) override;
	};

} /* namespace Cmds */

#endif /* SRC_COMMANDS_CUTDOWNTREES_H_ */
