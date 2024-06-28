#include "commands/CutDownTrees.hpp"

#include "ui/UI.hpp"
#include "game/TileCoordinates.hpp"
#include "game/District.hpp"
#include "entities/Tree.hpp"
#include "components/CanBeCutDownComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/TaskComponent.hpp"

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
