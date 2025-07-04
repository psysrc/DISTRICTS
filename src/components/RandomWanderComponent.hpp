#ifndef RANDOM_WANDER_COMPONENT_H_
#define RANDOM_WANDER_COMPONENT_H_

#include "components/Component.hpp"

/**
 * With this component, the entity will randomly move around the district.
 */
struct RandomWanderComponent : public Component
{
    RandomWanderComponent(unsigned int minWait, unsigned int maxWait)
        : minTicksToWait(minWait), maxTicksToWait(maxWait), ticksLeftToWait(0) {}

    virtual ~RandomWanderComponent() = default;

    unsigned int minTicksToWait;
    unsigned int maxTicksToWait;
    unsigned int ticksLeftToWait;
};

#endif /* RANDOM_WANDER_COMPONENT_H_ */
