#include "Sapling.h"

#include <memory>
#include "components/GrowComponent.h"
#include "components/PositionComponent.h"
#include "components/DrawComponent.h"

const int maxTicksToGrow = 1440;	// 6 mins
const int minTicksToGrow = 480;		// 2 mins

Sapling::Sapling() : Entity("Tree Sapling", ',') {
    int ticks = minTicksToGrow + (rand() % (maxTicksToGrow - minTicksToGrow + 1));

    addComponent<GrowComponent>(ticks);
    addComponent<PositionComponent>(this);
    addComponent<DrawComponent>(',');
}

Sapling::~Sapling() { }
