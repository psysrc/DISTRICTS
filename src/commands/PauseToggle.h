#ifndef SRC_COMMANDS_PAUSETOGGLE_H_
#define SRC_COMMANDS_PAUSETOGGLE_H_

#include <commands/PlayerCommand.h>

class District;

namespace Cmds {

class PauseToggle : public PlayerCommand {
public:
	PauseToggle();
	virtual ~PauseToggle();
	virtual void execute(District*) override;
};

} /* namespace Cmds */

#endif /* SRC_COMMANDS_PAUSETOGGLE_H_ */
