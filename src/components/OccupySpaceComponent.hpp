#ifndef OCCUPY_SPACE_COMPONENT_H_
#define OCCUPY_SPACE_COMPONENT_H_

#include "components/Component.hpp"

/**
 * Indicates that the entity occupies the whole tile that it is positioned on.
 * Only one entity with a `OccupySpaceComponent` can occupy a tile at any moment in time.
 * Entities without this component are free to occupy any tile, regardless of how many other entities there are.
 */
struct OccupySpaceComponent : public Component
{
    OccupySpaceComponent() {}

    virtual ~OccupySpaceComponent() = default;
};

#endif /* OCCUPY_SPACE_COMPONENT_H_ */
