#include "Sapling.h"

const int maxTicksToGrow = 1440;	// 6 mins
const int minTicksToGrow = 480;		// 2 mins

Sapling::Sapling() : Entity("Tree Sapling", ','), gp(GrowComponent(minTicksToGrow + (rand() % (maxTicksToGrow - minTicksToGrow + 1)))) {
	
}

Sapling::~Sapling() {

}
