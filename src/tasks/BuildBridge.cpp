#include "tasks/BuildBridge.h"

#include "game/Tile.h"
#include "game/TileProperty.h"
#include "game/District.h"
#include "deprecated/TileHelpers.h"
#include "components/TileComponent.h"

using namespace Tasks;

BuildBridge::BuildBridge(DeprecatedTile *pTile) : Task(pTile, "Build bridge", 25) {}

BuildBridge::~BuildBridge() {}

void BuildBridge::onCompletion(District* pDistrict)
{
	deprecatedGetTileEntity(pDistrict, getTile())->getComponent<TileComponent>()->property = TileProperty::Bridge;
}
