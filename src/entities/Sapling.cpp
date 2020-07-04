#include "Sapling.h"

#include "components/GrowComponent.h"
#include "components/PositionComponent.h"
#include "components/DrawComponent.h"

const int maxTicksToGrow = 1440;	// 6 mins
const int minTicksToGrow = 480;		// 2 mins

Sapling::Sapling() : Sapling(TileCoordinates(-1, -1)) {}

Sapling::Sapling(TileCoordinates coords) : Entity("Tree Sapling") {
    int ticks = minTicksToGrow + (rand() % (maxTicksToGrow - minTicksToGrow + 1));

    addComponent<GrowComponent>(ticks);
    addComponent<PositionComponent>(coords);
    addComponent<DrawComponent>(',');
}

Sapling::~Sapling() { }
