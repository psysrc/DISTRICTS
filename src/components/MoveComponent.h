#ifndef MOVE_COMPONENT_H_
#define MOVE_COMPONENT_H_

#include "components/Component.h"
#include "game/TileCoordinates.h"
#include "pathfinding/Path.h"

struct MoveComponent : public Component
{
    MoveComponent(TileCoordinates destination) : destination(destination) {}

    virtual ~MoveComponent() = default;

    TileCoordinates destination;
};

#endif /* MOVE_COMPONENT_H_ */
