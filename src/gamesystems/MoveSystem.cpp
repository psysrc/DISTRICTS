#include "gamesystems/MoveSystem.hpp"

#include "game/District.hpp"
#include "components/PositionComponent.hpp"
#include "components/MoveComponent.hpp"
#include "entities/OccupyRules.hpp"
#include "pathfinding/PathFinding.hpp"

MoveSystem::MoveSystem() {}

MoveSystem::~MoveSystem() {}

void MoveSystem::processEntity(District *district, const std::unique_ptr<Entity> &entity)
{
    MoveComponent *cmptMove = entity->getComponent<MoveComponent>();
    if (!cmptMove)
        return;

    PositionComponent *cmptPosition = entity->getComponent<PositionComponent>();
    if (!cmptPosition)
        return;

    // If the entity is already at its destination, it has finished moving
    if (cmptPosition->getPosition() == cmptMove->destination)
    {
        entity->removeComponent<MoveComponent>();
        return;
    }

    // If entity has a destination but no path, or has a path but has strayed from it, generate a new path
    if (!cmptMove->path || cmptPosition->getPosition() != cmptMove->path->current())
    {
        cmptMove->path = PathFinding::findPath(
            district, entity.get(), cmptPosition->getPosition(), cmptMove->destination, cmptMove->strictDestination);

        if (!cmptMove->path)
        {
            // Cannot find a valid path to the destination
            return;
        }
    }

    auto next = cmptMove->path->next();

    // If the end of the path has been reached, the entity has finished moving
    if (!next.has_value())
    {
        entity->removeComponent<MoveComponent>();
        return;
    }

    // If the entity cannot occupy the next tile along the path, generate a new path
    if (!OccupyRules::canOccupy(district, next.value()))
    {
        cmptMove->path = PathFinding::findPath(
            district, entity.get(), cmptPosition->getPosition(), cmptMove->destination, cmptMove->strictDestination);

        if (!cmptMove->path)
        {
            // Cannot find a valid path to the destination
            return;
        }

        next = cmptMove->path->next();

        // If the end of the path has been reached, the entity has finished moving
        if (!next.has_value())
        {
            entity->removeComponent<MoveComponent>();
            return;
        }
    }

    if (!OccupyRules::canOccupy(district, next.value()))
        throw std::runtime_error("Just generated a brand new path for an entity, but the entity cannot occupy the next tile along the path");

    // Move the entity along the path
    cmptPosition->setPosition(next.value());

    // If the entity is now at its destination, it has finished moving
    if (cmptPosition->getPosition() == cmptMove->destination)
    {
        entity->removeComponent<MoveComponent>();
        return;
    }
}
