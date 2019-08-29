#include "Sapling.h"

Sapling::Sapling(District* district) : Entity(district, "Tree Sapling", ',') {

}

Sapling::~Sapling() {

}

void Sapling::simulate() {
	if (rand() % 100 < 2) {		// 2% chance of becoming a tree
		Tree* tree = pDistrict->makeEntity<Tree>();

		pTile->vacateEntity();
		pTile->occupy(tree);
		tree->setTile(pTile);

		deleteEntity();
	}
}
