#include <tasks/CutDownTree.h>
#include "entities/Tree.h"
#include "game/Tile.h"

CutDownTree::CutDownTree(District* district, Tile* tile) : Task(district, tile, "Cut down tree", 10) {

}

CutDownTree::~CutDownTree() {

}

void CutDownTree::onCompletion() {
	// Remove the tree from the tile
	Tree* pTree = dynamic_cast<Tree*>(getTile()->vacateEntity());
	pTree->setTile(nullptr);

	pTree->deleteEntity();	// Delete the Tree
}
