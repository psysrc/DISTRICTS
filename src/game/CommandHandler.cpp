#include <game/CommandHandler.h>

#include "ui/UI.h"
#include "entities/Tree.h"
#include "game/Tile.h"
#include "game/District.h"
#include "tasks/CutDownTree.h"
#include "tasks/BuildBridge.h"

District* CommandHandler::pDistrict = nullptr;

/*
 * Handles a command on behalf of the Game.
 */
void CommandHandler::handle(District* pDistrict, PlayerCommand::PlayerCommand command) {
	CommandHandler::pDistrict = pDistrict;

	switch (command) {
	case PlayerCommand::CutDownTrees:
		cutDownTrees();
		break;
	case PlayerCommand::BuildBridge:
		buildBridge();
		break;
	default:
		break;
	}

	CommandHandler::pDistrict = nullptr;
}

void CommandHandler::cutDownTrees() {
	Tile* selectedTile = UI::selectTile(pDistrict);

	if (selectedTile != nullptr) {	// Did the player make a selection?
		if (dynamic_cast<Tree*>(selectedTile->getEntity()) != nullptr)	// Does the selected tile actually have a tree?
			pDistrict->makeTask<Tasks::CutDownTree>(selectedTile);
	}
}

void CommandHandler::buildBridge() {
	Tile* selectedTile = UI::selectTile(pDistrict);

	if (selectedTile != nullptr) {
		if (selectedTile->getProperty() == TileProperty::Water)
			pDistrict->makeTask<Tasks::BuildBridge>(selectedTile);
	}
}

