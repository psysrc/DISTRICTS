#include "commands/Quit.hpp"

namespace Cmds
{

    Quit::Quit() : PlayerCommand("Quit game") {}

    Quit::~Quit() {}

    void Quit::execute(District * /* pDistrict */) {}

} /* namespace Cmds */
