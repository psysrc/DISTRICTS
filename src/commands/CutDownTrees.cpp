#include <commands/CutDownTrees.h>

#include "ui/UI.h"
#include "game/Tile.h"
#include "game/District.h"
#include "tasks/CutDownTree.h"
#include "entities/Tree.h"

namespace Cmds {

CutDownTrees::CutDownTrees() : PlayerCommand("Cut down trees") {}

CutDownTrees::~CutDownTrees() {}

void CutDownTrees::execute(District* pDistrict) {
	Tile* pSelectedTile = UI::selectTile(pDistrict);

	if (pSelectedTile != nullptr) {	// Did the player make a selection?
		if (dynamic_cast<Tree*>(pSelectedTile->getEntity()) != nullptr)	// Does the selected tile actually have a tree?
		{
			bool taskAlreadyExists = false;

			// Check all existing tasks on this tile
			for (Tasks::Task* pExistingTask : pSelectedTile->getTasks())
			{
				// If a CutDownTree task already exists...
				if (dynamic_cast<Tasks::CutDownTree*>(pExistingTask) != nullptr)
					taskAlreadyExists = true;
			}

			// ... Then don't create another one
			if (!taskAlreadyExists)
				pDistrict->makeTask<Tasks::CutDownTree>(pSelectedTile, pDistrict);
		}
	}
}

} /* namespace Cmds */
