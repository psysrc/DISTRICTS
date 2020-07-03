#include "CutDownTree.h"

#include "entities/Tree.h"
#include "game/Tile.h"
#include "game/District.h"
#include "components/PositionComponent.h"

using namespace Tasks;

CutDownTree::CutDownTree(Tile* tile, District* district) : Task(tile, "Cut down tree", 10), pDistrict(district) {}

CutDownTree::~CutDownTree() {}

void CutDownTree::onCompletion() {
	// Remove the tree from the tile
	Tree* pTree = dynamic_cast<Tree*>(getTile()->vacateEntity());
	pTree->getComponent<PositionComponent>()->setTile(nullptr);

	pDistrict->deleteEntity(pTree);	// Delete the Tree
}
