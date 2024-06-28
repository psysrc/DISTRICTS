#ifndef NAME_COMPONENT_H_
#define NAME_COMPONENT_H_

#include "components/Component.hpp"
#include <string>

struct NameComponent : public Component
{
    NameComponent(const std::string& name) : name(name) {}

    virtual ~NameComponent() = default;

    std::string name;
};

#endif /* NAME_COMPONENT_H_ */
