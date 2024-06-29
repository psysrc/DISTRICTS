#ifndef GROWCOMPONENT_H_
#define GROWCOMPONENT_H_

#include "components/Component.hpp"
#include "game/TickSpeed.hpp"
#include <functional>

/**
 * A feature of an entity that means it will eventually turn into ("grow into") another entity.
 * For example, a tree sapling eventually grows into a full tree. Or a baby animal turns into a fully grown animal.
 */
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
