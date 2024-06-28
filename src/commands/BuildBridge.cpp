#include "commands/BuildBridge.hpp"

#include "ui/UI.hpp"
#include "game/TileCoordinates.hpp"
#include "game/District.hpp"
#include "components/TaskComponent.hpp"
#include "components/TileComponent.hpp"
#include "components/PositionComponent.hpp"
#include <sstream>

namespace Cmds
{

	BuildBridge::BuildBridge() : PlayerCommand("Build a bridge") {}

	BuildBridge::~BuildBridge() {}

	void BuildBridge::execute(District *pDistrict)
	{
		const auto selection = UI::selectTileCoordinates(pDistrict);

		if (selection.has_value())  // Check that the player selected a tile
		{
			auto coords = selection.value();
			const auto &entities = pDistrict->getEntitiesAtPosition(coords);

			const auto it = std::find_if(entities.begin(), entities.end(),
										 [](Entity *e)
										 { return e->hasComponent<TileComponent>(); });

			const auto tile = *it;

			// Check that the tile is water
			if (tile->getComponent<TileComponent>()->property == TileProperty::Water)
			{
				if (!tile->hasComponent<TaskComponent>())
				{
					auto onCompletion = [tile]()
					{
						tile->getComponent<TileComponent>()->property = TileProperty::Bridge;
					};

					tile->addComponent(std::make_unique<TaskComponent>(tile, 25, onCompletion));
				}
			}
		}
	}

} /* namespace Cmds */
