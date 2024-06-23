#include <commands/BuildBridge.h>

#include "ui/UI.h"
#include "game/Tile.h"
#include "game/District.h"
#include "components/TaskComponent.h"
#include "deprecated/TileHelpers.h"
#include "components/TileComponent.h"
#include <components/PositionComponent.h>
#include <sstream>

namespace Cmds
{

	BuildBridge::BuildBridge() : PlayerCommand("Build a bridge") {}

	BuildBridge::~BuildBridge() {}

	void BuildBridge::execute(District *pDistrict)
	{
		DeprecatedTile *pSelectedTile = UI::selectTile(pDistrict);

		if (pSelectedTile != nullptr)  // Check that the player selected a tile
		{
			Entity* tile = deprecatedGetTileEntity(pDistrict, pSelectedTile);

			// Check that the tile is water
			if (tile->getComponent<TileComponent>()->property == TileProperty::Water)
			{
				if (!tile->hasComponent<TaskComponent>())
				{
					auto onCompletion = [tile]()
					{
						tile->getComponent<TileComponent>()->property = TileProperty::Bridge;
					};

					tile->addComponent(std::make_unique<TaskComponent>(25, onCompletion));
				}
			}
		}
	}

} /* namespace Cmds */
