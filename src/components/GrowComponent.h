#ifndef GROWCOMPONENT_H_
#define GROWCOMPONENT_H_

#include "components/Component.h"

class GrowComponent : public Component {
public:
    GrowComponent() : ticksToGrow(0) {}
    GrowComponent(int growTicks) : ticksToGrow(growTicks) {}
    virtual ~GrowComponent() {}

    int ticksToGrow;
};

#endif /* GROWCOMPONENT_H_ */