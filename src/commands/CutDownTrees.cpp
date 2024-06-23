#include "commands/CutDownTrees.h"

#include "ui/UI.h"
#include "game/Tile.h"
#include "game/District.h"
#include "entities/Tree.h"
#include "components/CanBeCutDownComponent.h"
#include "deprecated/TileHelpers.h"
#include "components/PositionComponent.h"
#include "components/TaskComponent.h"

namespace Cmds
{

	CutDownTrees::CutDownTrees() : PlayerCommand("Cut down trees") {}

	CutDownTrees::~CutDownTrees() {}

	void CutDownTrees::execute(District *pDistrict)
	{
		DeprecatedTile *pSelectedTile = UI::selectTile(pDistrict);

		if (pSelectedTile != nullptr) // Did the player make a selection?
		{
			auto tile = deprecatedGetTileEntity(pDistrict, pSelectedTile);
			const auto coords = tile->getComponent<PositionComponent>()->getPosition();
			const auto &entities = pDistrict->entitiesAtPosition(coords);

			const auto it = std::find_if(entities.begin(), entities.end(),
										 [](Entity *e)
										 { return e->hasComponent<CanBeCutDownComponent>(); });

			if (it != entities.end()) // Does the position have a tree?
			{
				const auto tree = *it;
				if (!tree->hasComponent<TaskComponent>()) // Does the tree already have a task?
				{
					auto onCompletion = [pDistrict, tree]()
					{
						pDistrict->deleteEntity(tree);
					};

					tree->addComponent(std::make_unique<TaskComponent>(10, onCompletion));
				}
			}
		}
	}

} /* namespace Cmds */
