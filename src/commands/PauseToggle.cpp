#include "commands/PauseToggle.hpp"

namespace Cmds
{

    PauseToggle::PauseToggle() : PlayerCommand("Pause or unpause the game") {}

    PauseToggle::~PauseToggle() {}

    void PauseToggle::execute(District * /* pDistrict */) {}

} /* namespace Cmds */
