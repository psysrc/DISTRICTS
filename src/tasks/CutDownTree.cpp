#include "CutDownTree.h"

#include "entities/Tree.h"
#include "game/Tile.h"
#include "game/District.h"
#include "components/PositionComponent.h"

using namespace Tasks;

CutDownTree::CutDownTree(Tile* pTile, District* pDistrict) : Task(pTile, "Cut down tree", 10), pDistrict(pDistrict) {}

CutDownTree::~CutDownTree() {}

void CutDownTree::onCompletion() {
	// Remove the tree from the tile
	pDistrict->deleteEntity(getTile()->getEntity());
}
