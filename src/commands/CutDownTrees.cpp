#include "commands/CutDownTrees.h"

#include "ui/UI.h"
#include "game/TileCoordinates.h"
#include "game/District.h"
#include "entities/Tree.h"
#include "components/CanBeCutDownComponent.h"
#include "components/PositionComponent.h"
#include "components/TaskComponent.h"

namespace Cmds
{

	CutDownTrees::CutDownTrees() : PlayerCommand("Cut down trees") {}

	CutDownTrees::~CutDownTrees() {}

	void CutDownTrees::execute(District *pDistrict)
	{
		const auto selection = UI::selectTileCoordinates(pDistrict);

		if (selection.has_value()) // Did the player make a selection?
		{
			auto coords = selection.value();
			const auto &entities = pDistrict->getEntitiesAtPosition(coords);

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

					tree->addComponent(std::make_unique<TaskComponent>(tree, 10, onCompletion));
				}
			}
		}
	}

} /* namespace Cmds */
