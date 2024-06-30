#ifndef ACQUATIC_COMPONENT_H_
#define ACQUATIC_COMPONENT_H_

#include "components/Component.hpp"

/**
 * Indicates that an entity is acquatic, and can occupy Water tiles.
 */
struct AcquaticComponent : public Component
{
    AcquaticComponent() {}

    virtual ~AcquaticComponent() = default;
};

#endif /* ACQUATIC_COMPONENT_H_ */
