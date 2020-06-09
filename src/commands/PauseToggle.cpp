#include <commands/PauseToggle.h>

namespace Cmds {

PauseToggle::PauseToggle() : PlayerCommand("Pause or unpause the game") {

}

PauseToggle::~PauseToggle() {

}

void PauseToggle::execute(__attribute__((unused)) District* pDistrict) {}

} /* namespace Cmds */
