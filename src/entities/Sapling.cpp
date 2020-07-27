#include "Sapling.h"

#include "components/GrowComponent.h"
#include "components/PositionComponent.h"
#include "components/DrawComponent.h"

const int maxSecondsToGrow = 6 * 60;
const int minSecondsToGrow = 2 * 60;

Sapling::Sapling() : Sapling(TileCoordinates(-1, -1)) {}

Sapling::Sapling(TileCoordinates coords) : Entity("Tree Sapling") {
    int seconds = minSecondsToGrow + (rand() % (maxSecondsToGrow - minSecondsToGrow + 1));

    addComponent<GrowComponent>(seconds);
    addComponent<PositionComponent>(coords);
    addComponent<DrawComponent>(',');
}

Sapling::~Sapling() { }
