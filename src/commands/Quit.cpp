#include <commands/Quit.h>

namespace Cmds {

Quit::Quit() : PlayerCommand("Quit game") {

}

Quit::~Quit() {

}

void Quit::execute(__attribute__((unused)) District* pDistrict) {}

} /* namespace Cmds */
