#ifndef COMPONENT_H_
#define COMPONENT_H_

/**
 * Base class for all Components in the DISTRICTS ECS (Entity Component System).
 * Components are intended to be plain data objects. GameSystems contain the logic that acts upon them.
 */
struct Component
{
    Component() {}

    virtual ~Component() = default;
};

#endif /* COMPONENT_H_ */
