#include "tasks/BuildBridge.h"

#include "game/Tile.h"
#include "game/TileProperty.h"

using namespace Tasks;

BuildBridge::BuildBridge(Tile *pTile) : Task(pTile, "Build bridge", 25) {}

BuildBridge::~BuildBridge() {}

void BuildBridge::onCompletion()
{
	getTile()->updateProperty(TileProperty::Bridge);
}
