#ifndef CITIZENCOMPONENT_H_
#define CITIZENCOMPONENT_H_

#include "components/Component.hpp"

/**
 * Identifies an entity as a Citizen, one of the core features of the game.
 * Citizens are humans which are trying to settle a base and live off of the land.
 * They work, gather , build, dismantle, explore, eat, drink, etc.
 */
struct CitizenComponent : public Component
{
    CitizenComponent() {}

    virtual ~CitizenComponent() = default;
};

#endif /* CITIZENCOMPONENT_H_ */
