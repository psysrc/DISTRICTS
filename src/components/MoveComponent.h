#ifndef MOVE_COMPONENT_H_
#define MOVE_COMPONENT_H_

#include "components/Component.h"
#include "game/TileCoordinates.h"
#include "pathfinding/Path.h"

struct MoveComponent : public Component
{
    MoveComponent(TileCoordinates destination, bool strictDestination) :
        destination(destination), strictDestination(strictDestination) {}

    virtual ~MoveComponent() = default;

    TileCoordinates destination;
    bool strictDestination;
    std::unique_ptr<Path> path;
};

#endif /* MOVE_COMPONENT_H_ */
