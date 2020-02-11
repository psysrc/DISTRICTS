#ifndef SRC_COMMANDS_QUIT_H_
#define SRC_COMMANDS_QUIT_H_

#include <commands/PlayerCommand.h>

class District;

namespace Cmds {

class Quit : public PlayerCommand {
public:
	Quit();
	virtual ~Quit();
	virtual void execute(District*) override;
};

} /* namespace Cmds */

#endif /* SRC_COMMANDS_QUIT_H_ */
