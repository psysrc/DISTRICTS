#include <commands/BuildBridge.h>

#include "ui/UI.h"
#include "game/Tile.h"
#include "game/District.h"
#include "tasks/BuildBridge.h"

namespace Cmds {

BuildBridge::BuildBridge() : PlayerCommand("Build a bridge") {

}

BuildBridge::~BuildBridge() {

}

void BuildBridge::execute(District* pDistrict) {
	Tile* selectedTile = UI::selectTile(pDistrict);

	if (selectedTile != nullptr) {
		if (selectedTile->getProperty() == TileProperty::Water)
			pDistrict->makeTask<Tasks::BuildBridge>(selectedTile);
	}
}

} /* namespace Cmds */
