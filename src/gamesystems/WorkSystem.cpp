#include "gamesystems/WorkSystem.h"

#include <memory>
#include "entities/Entity.h"
#include "game/District.h"
#include "components/WorkOnTaskComponent.h"
#include "components/PositionComponent.h"
#include "components/MoveComponent.h"
#include "components/TaskComponent.h"
#include "pathfinding/PathFinding.h"

WorkSystem::WorkSystem() {}

WorkSystem::~WorkSystem() {}

void WorkSystem::run(District * district)
{
    for (const std::unique_ptr<Entity> &entity : district->getEntities())
    {
        WorkOnTaskComponent *cmptWorkOnTask = entity->getComponent<WorkOnTaskComponent>();
        if (!cmptWorkOnTask)
            continue;

        Entity* const taskEntity = district->getEntity(cmptWorkOnTask->entityID);
        if (!taskEntity)
        {
            // If this WorkOnTask component refers to a non-existent entity, delete the WorkOnTask component
            entity->removeComponent<WorkOnTaskComponent>();
            continue;
        }

        TaskComponent* const cmptTask = taskEntity->getComponent<TaskComponent>();
        if (!cmptTask)
        {
            // If this WorkOnTask component refers to an entity that doesn't have a task, delete the WorkOnTask component
            entity->removeComponent<WorkOnTaskComponent>();
            continue;
        }

        const PositionComponent* const cmptPositionEntity = entity->getComponent<PositionComponent>();
        const PositionComponent* const cmptPositionTask = taskEntity->getComponent<PositionComponent>();
        if (!cmptPositionEntity || !cmptPositionTask)
            continue;

        const TileCoordinates entityPosition = cmptPositionEntity->getPosition();
        const TileCoordinates taskPosition = cmptPositionTask->getPosition();

        // If the entity is not in range to work on the task, wait until it is closer
        if (PathFinding::euclideanDistance(entityPosition, taskPosition) > 1.5)
        {
            if (!entity->hasComponent<MoveComponent>())
            {
                entity->addComponent(std::make_unique<MoveComponent>(taskPosition, false));
            }

            continue;
        }

        --(cmptTask->workRemaining);  // Entity is in range of the task - do one unit of work

        if (cmptTask->workRemaining == 0)
        {
            cmptTask->onCompletion();
            taskEntity->removeComponent<TaskComponent>();
            entity->removeComponent<WorkOnTaskComponent>();
        }
    }
}
