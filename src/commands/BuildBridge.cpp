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
			if (!pSelectedTile->hasTask<Tasks::BuildBridge>())
				pDistrict->makeTask<Tasks::BuildBridge>(pSelectedTile);
		}
	}
}

} /* namespace Cmds */
