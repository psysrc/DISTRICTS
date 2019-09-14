#include "Sapling.h"

#include "game/Tile.h"
#include "game/District.h"
#include "tasks/CutDownTree.h"
#include "entities/Tree.h"

Sapling::Sapling(District* district) : Entity(district, "Tree Sapling", ',') {

}

Sapling::~Sapling() {

}

void Sapling::simulate() {
	if (rand() % 100 < 1) {		// 1% chance of becoming a tree
		Tree* tree = pDistrict->makeEntity<Tree>();

		pTile->vacateEntity();
		pTile->occupy(tree);
		tree->setTile(pTile);

		deleteEntity();
	}
}
