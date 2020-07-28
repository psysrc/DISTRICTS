#include <commands/BuildBridge.h>

#include "ui/UI.h"
#include "game/Tile.h"
#include "game/District.h"
#include "tasks/BuildBridge.h"

namespace Cmds {

BuildBridge::BuildBridge() : PlayerCommand("Build a bridge") {}

BuildBridge::~BuildBridge() {}

void BuildBridge::execute(District* pDistrict) {
	Tile* pSelectedTile = UI::selectTile(pDistrict);

	if (pSelectedTile != nullptr) {	// Check that the player selected a tile
		if (pSelectedTile->getProperty() == TileProperty::Water)	// Check that the tile is water
		{
			bool taskAlreadyExists = false;

			for (Tasks::Task* pExistingTask : pSelectedTile->getTasks())
			{
				if (dynamic_cast<Tasks::BuildBridge*>(pExistingTask) != nullptr)
					taskAlreadyExists = true;
			}

			// Do not create a BuildBridge task if one already exists on this tile
			if (!taskAlreadyExists)
				pDistrict->makeTask<Tasks::BuildBridge>(pSelectedTile);
		}
	}
}

} /* namespace Cmds */
