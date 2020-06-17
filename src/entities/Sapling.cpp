#include "Sapling.h"

#include <memory>
#include "components/GrowComponent.h"

const int maxTicksToGrow = 1440;	// 6 mins
const int minTicksToGrow = 480;		// 2 mins

Sapling::Sapling() : Entity("Tree Sapling", ',') {
    int ticks = minTicksToGrow + (rand() % (maxTicksToGrow - minTicksToGrow + 1));

	components.push_back(std::make_unique<GrowComponent>(ticks));
}

Sapling::~Sapling() { }
