#ifndef NAME_COMPONENT_H_
#define NAME_COMPONENT_H_

#include "components/Component.h"
#include <string>

class NameComponent : public Component
{
public:
    NameComponent(const std::string& name) : name(name) {}
    virtual ~NameComponent() {}

    std::string name;
};

#endif /* NAME_COMPONENT_H_ */
