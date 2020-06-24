#include <tasks/BuildBridge.h>

#include <game/Tile.h>
#include <game/Constants.h>

using namespace Tasks;

BuildBridge::BuildBridge(District* district, Tile* tile) : Task(tile, "Build bridge", 25) {

}

BuildBridge::~BuildBridge() {

}

void BuildBridge::onCompletion() {
	getTile()->updateProperty(TileProperty::Bridge);
}

