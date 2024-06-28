#ifndef MOVE_COMPONENT_H_
#define MOVE_COMPONENT_H_

#include "components/Component.hpp"
#include "game/TileCoordinates.hpp"
#include "pathfinding/Path.hpp"

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
