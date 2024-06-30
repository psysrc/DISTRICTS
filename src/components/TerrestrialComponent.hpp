#ifndef TERRESTRIAL_COMPONENT_H_
#define TERRESTRIAL_COMPONENT_H_

#include "components/Component.hpp"

/**
 * Indicates that an entity is terrestrial, and can occupy land tiles.
 */
struct TerrestrialComponent : public Component
{
    TerrestrialComponent() {}

    virtual ~TerrestrialComponent() = default;
};

#endif /* TERRESTRIAL_COMPONENT_H_ */
