#include "gamesystems/MoveSystem.h"

#include "game/District.h"
#include "components/PositionComponent.h"
#include "components/MoveComponent.h"
#include "entities/OccupyRules.h"
#include "pathfinding/PathFinding.h"

MoveSystem::MoveSystem() {}

MoveSystem::~MoveSystem() {}

void MoveSystem::run(District *district)
{
    for (const std::unique_ptr<Entity> &entity : district->getEntities())
    {
        MoveComponent *cmptMove = entity->getComponent<MoveComponent>();
        if (!cmptMove)
            continue;

        PositionComponent *cmptPosition = entity->getComponent<PositionComponent>();
        if (!cmptPosition)
            continue;

        // If the entity is already at its destination, it has finished moving
        if (cmptPosition->getPosition() == cmptMove->destination)
        {
            entity->removeComponent<MoveComponent>();
            continue;
        }

        // If entity has a destination but no path, or has a path but has strayed from it, generate a new path
        if (!cmptMove->path || cmptPosition->getPosition() != cmptMove->path->current())
        {
            cmptMove->path = PathFinding::findPath(
                district, entity.get(), cmptPosition->getPosition(), cmptMove->destination, cmptMove->strictDestination);

            if (!cmptMove->path)
            {
                // Cannot find a valid path to the destination
                continue;
            }
        }

        auto next = cmptMove->path->next();

        // If the end of the path has been reached, the entity has finished moving
        if (!next.has_value())
        {
            entity->removeComponent<MoveComponent>();
            continue;
        }

        // If the entity cannot occupy the next tile along the path, generate a new path
        if (!OccupyRules::canOccupy(district, next.value()))
        {
            cmptMove->path = PathFinding::findPath(
                district, entity.get(), cmptPosition->getPosition(), cmptMove->destination, cmptMove->strictDestination);

            if (!cmptMove->path)
            {
                // Cannot find a valid path to the destination
                continue;
            }

            next = cmptMove->path->next();

            // If the end of the path has been reached, the entity has finished moving
            if (!next.has_value())
            {
                entity->removeComponent<MoveComponent>();
                continue;
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
            continue;
        }
    }
}
