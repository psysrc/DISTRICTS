#include <commands/BuildBridge.h>

#include "ui/UI.h"
#include "game/Tile.h"
#include "game/District.h"
#include "tasks/BuildBridge.h"
#include "deprecated/TileHelpers.h"
#include "components/TileComponent.h"

namespace Cmds
{

	BuildBridge::BuildBridge() : PlayerCommand("Build a bridge") {}

	BuildBridge::~BuildBridge() {}

	void BuildBridge::execute(District *pDistrict)
	{
		DeprecatedTile *pSelectedTile = UI::selectTile(pDistrict);

		if (pSelectedTile != nullptr)  // Check that the player selected a tile
		{
			// Check that the tile is water
			if (deprecatedGetTileEntity(pDistrict, pSelectedTile)->getComponent<TileComponent>()->property == TileProperty::Water)
			{
				if (!pSelectedTile->hasTask<Tasks::BuildBridge>())
					pDistrict->makeTask<Tasks::BuildBridge>(pSelectedTile);
			}
		}
	}

} /* namespace Cmds */
