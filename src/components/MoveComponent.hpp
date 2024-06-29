#ifndef MOVE_COMPONENT_H_
#define MOVE_COMPONENT_H_

#include "components/Component.hpp"
#include "game/TileCoordinates.hpp"
#include "pathfinding/Path.hpp"

/**
 * If an entity has a MoveComponent, it will move towards its destination.
 * More specifically, its position will be updated over time.
 */
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
