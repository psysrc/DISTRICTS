#include <commands/CutDownTrees.h>

#include "ui/UI.h"
#include "game/Tile.h"
#include "game/District.h"
#include "tasks/CutDownTree.h"
#include "entities/Tree.h"
#include "components/CanBeCutDownComponent.h"

namespace Cmds
{

	CutDownTrees::CutDownTrees() : PlayerCommand("Cut down trees") {}

	CutDownTrees::~CutDownTrees() {}

	void CutDownTrees::execute(District *pDistrict)
	{
		DeprecatedTile *pSelectedTile = UI::selectTile(pDistrict);

		if (pSelectedTile != nullptr) // Did the player make a selection?
		{
			if (!pSelectedTile->hasTask<Tasks::CutDownTree>())  // Does the position already have a task?
			{
				const auto &entities = pDistrict->entitiesAtPosition(pSelectedTile->getCoordinates());
				const auto it = std::find_if(entities.begin(), entities.end(), [](Entity *e)
											 { return e->hasComponent<CanBeCutDownComponent>(); });
				if (it != entities.end())
				{
					auto task = std::make_shared<Tasks::CutDownTree>(pSelectedTile, pDistrict, *it);
					pDistrict->addTask(task);
				}
			}
		}
	}

} /* namespace Cmds */
