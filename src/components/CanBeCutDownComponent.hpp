#ifndef CAN_BE_CUT_DOWN_COMPONENT_H_
#define CAN_BE_CUT_DOWN_COMPONENT_H_

#include "components/Component.hpp"

/**
 * Indicates that an entity can be "cut down". This may be to acquire resources or to remove the entity.
 * This is a core feature of trees.
 */
struct CanBeCutDownComponent : public Component
{
    CanBeCutDownComponent() {}

    virtual ~CanBeCutDownComponent() = default;
};

#endif /* CAN_BE_CUT_DOWN_COMPONENT_H_ */
