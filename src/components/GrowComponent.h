#ifndef GROWCOMPONENT_H_
#define GROWCOMPONENT_H_

#include "components/Component.h"

class GrowSystem;

class GrowComponent : public Component {
public:
    GrowComponent(int growTicks) : ticksToGrow(growTicks) {}
    virtual ~GrowComponent() {}

private:
    int ticksToGrow;
    friend class GrowSystem;
};

#endif /* GROWCOMPONENT_H_ */