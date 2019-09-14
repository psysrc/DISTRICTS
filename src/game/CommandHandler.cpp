#include <game/CommandHandler.h>

void CommandHandler::handle(PlayerCommand command) {
	switch (command) {
	case CutDownTrees:
		cutDownTrees();
		break;
	default:
		break;
	}
}

void CommandHandler::cutDownTrees() {

}
