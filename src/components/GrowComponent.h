#ifndef GROWCOMPONENT_H_
#define GROWCOMPONENT_H_

#include "components/Component.h"
#include "game/TickSpeed.h"
#include <functional>

struct GrowComponent : public Component
{
    // A function which returns a new entity to "grow" into, given the current entity
    using MakeNextEntityMethod_t = std::function<std::unique_ptr<Entity>(const Entity&)>;

    GrowComponent(MakeNextEntityMethod_t makeNextEntity, int ticksToGrow)
        : makeNextEntity(makeNextEntity), ticksToGrow(ticksToGrow) {}

    virtual ~GrowComponent() = default;

    MakeNextEntityMethod_t makeNextEntity;
    int ticksToGrow;
};

#endif /* GROWCOMPONENT_H_ */
