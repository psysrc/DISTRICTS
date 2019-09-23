#include <commands/CutDownTrees.h>

#include "ui/UI.h"
#include "game/Tile.h"
#include "game/District.h"
#include "tasks/CutDownTree.h"
#include "entities/Tree.h"

namespace Cmds {

CutDownTrees::CutDownTrees() : PlayerCommand("Cut down trees") {

}

CutDownTrees::~CutDownTrees() {

}

void CutDownTrees::execute(District* pDistrict) {
	Tile* selectedTile = UI::selectTile(pDistrict);

	if (selectedTile != nullptr) {	// Did the player make a selection?
		if (dynamic_cast<Tree*>(selectedTile->getEntity()) != nullptr)	// Does the selected tile actually have a tree?
			pDistrict->makeTask<Tasks::CutDownTree>(selectedTile);
	}
}

} /* namespace Cmds */
