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
		Tile *pSelectedTile = UI::selectTile(pDistrict);

		if (pSelectedTile != nullptr) // Did the player make a selection?
		{
			Entity *pEntity = pSelectedTile->getEntity();
			if (pEntity != nullptr) // Does the tile have an entity on it?
			{
				if (pEntity->hasComponent<CanBeCutDownComponent>()) // Can the entity be cut down?
				{
					if (!pSelectedTile->hasTask<Tasks::CutDownTree>())
						pDistrict->makeTask<Tasks::CutDownTree>(pSelectedTile, pDistrict);
				}
			}
		}
	}

} /* namespace Cmds */
