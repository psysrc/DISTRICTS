#ifndef NAME_COMPONENT_H_
#define NAME_COMPONENT_H_

#include "components/Component.hpp"
#include <string>

/**
 * A display name for an entity.
 * For example, each Citizen will have a unique name.
 */
struct NameComponent : public Component
{
    NameComponent(const std::string& name) : name(name) {}

    virtual ~NameComponent() = default;

    std::string name;
};

#endif /* NAME_COMPONENT_H_ */
