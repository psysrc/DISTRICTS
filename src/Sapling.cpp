#include "Sapling.h"

Sapling::Sapling(District* district) : Entity(district, "Tree Sapling", ',') {

}

Sapling::~Sapling() {

}

void Sapling::simulate() {
	if (rand() % 100 < 2) {		// 2% chance of becoming a tree
		// TODO: Swap this Sapling entity on the tile for a Tree entity
//		drawSymbol = '$';	// Temporary illusion of growth
//		pTile->updateVisuals();

//		Tree* tree = pDistrict->makeEntity<Tree>();
		pTile->vacateEntity();

		deleteEntity();
	}

	UserInterface::displayDebugMessage("Tree sapling alive!");
}
