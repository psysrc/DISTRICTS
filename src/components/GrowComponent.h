#ifndef GROWCOMPONENT_H_
#define GROWCOMPONENT_H_

#include "components/Component.h"
#include "game/TickSpeed.h"
#include <functional>

class GrowSystem;

class GrowComponent : public Component
{
public:
    // A function which returns a new entity to "grow" into, given the current entity
    using MakeNextEntityMethod_t = std::function<std::unique_ptr<Entity>(const Entity&)>;

    GrowComponent(int seconds, MakeNextEntityMethod_t nextEntityMethod)
        : ticksToGrow(seconds * ticksPerSecond),
          makeNextEntity(std::move(nextEntityMethod)) {}

    virtual ~GrowComponent() {}

private:
    int ticksToGrow;
    MakeNextEntityMethod_t makeNextEntity;
    friend class GrowSystem;
};

#endif /* GROWCOMPONENT_H_ */
