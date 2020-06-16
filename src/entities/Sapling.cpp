#include "Sapling.h"

#include "game/Tile.h"
#include "game/District.h"
#include "tasks/CutDownTree.h"
#include "entities/Tree.h"

const int maxTicksToGrow = 1440;	// 6 mins
const int minTicksToGrow = 480;		// 2 mins

Sapling::Sapling(District* district) : Entity(district, "Tree Sapling", ',') {
	ticksToGrow = minTicksToGrow + (rand() % (maxTicksToGrow - minTicksToGrow + 1));
}

Sapling::~Sapling() {

}

void Sapling::simulate() {
	ticksToGrow--;

	if (ticksToGrow <= 0) {
		pTile->vacateEntity();
		pDistrict->makeEntity<Tree>(pTile);

		pDistrict->deleteEntity(this);
	}
}
