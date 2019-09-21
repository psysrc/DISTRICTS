#include "Sapling.h"

#include "game/Tile.h"
#include "game/District.h"
#include "tasks/CutDownTree.h"
#include "entities/Tree.h"

const int maxTicksToGrow = 90;	// 6 mins
const int minTicksToGrow = 30;	// 2 mins

Sapling::Sapling(District* district) : Entity(district, "Tree Sapling", ',') {
	ticksToGrow = minTicksToGrow + (rand() % (maxTicksToGrow - minTicksToGrow + 1));
}

Sapling::~Sapling() {

}

void Sapling::simulate() {
	ticksToGrow--;

	if (ticksToGrow <= 0) {
		Tree* tree = pDistrict->makeEntity<Tree>();

		pTile->vacateEntity();
		pTile->occupy(tree);
		tree->setTile(pTile);

		deleteEntity();
	}
}
