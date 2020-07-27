#ifndef GROWCOMPONENT_H_
#define GROWCOMPONENT_H_

#include "components/Component.h"
#include "game/TickSpeed.h"

class GrowSystem;

class GrowComponent : public Component {
public:
    GrowComponent(int seconds) : ticksToGrow(seconds * ticksPerSecond) {}
    virtual ~GrowComponent() {}

private:
    int ticksToGrow;
    friend class GrowSystem;
};

#endif /* GROWCOMPONENT_H_ */