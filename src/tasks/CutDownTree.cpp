#include "CutDownTree.h"

#include "entities/Tree.h"
#include "game/Tile.h"
#include "game/District.h"
#include "components/PositionComponent.h"

using namespace Tasks;

CutDownTree::CutDownTree(DeprecatedTile *pTile, District *pDistrict, Entity* tree) : Task(pTile, "Cut down tree", 10), pDistrict(pDistrict), tree(tree) {}

CutDownTree::~CutDownTree() {}

void CutDownTree::onCompletion(District*)
{
	pDistrict->deleteEntity(tree);
}
