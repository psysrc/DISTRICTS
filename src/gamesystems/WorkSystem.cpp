#include "gamesystems/WorkSystem.hpp"

#include <memory>
#include "entities/Entity.hpp"
#include "game/District.hpp"
#include "components/WorkOnTaskComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/MoveComponent.hpp"
#include "components/TaskComponent.hpp"
#include "pathfinding/PathFinding.hpp"

WorkSystem::WorkSystem() {}

WorkSystem::~WorkSystem() {}

void WorkSystem::processEntity(District *district, const std::unique_ptr<Entity> &entity)
{
    WorkOnTaskComponent *cmptWorkOnTask = entity->getComponent<WorkOnTaskComponent>();
    if (!cmptWorkOnTask)
        return;

    Entity *const taskEntity = district->getEntity(cmptWorkOnTask->entityID);
    if (!taskEntity)
    {
        // If this WorkOnTask component refers to a non-existent entity, delete the WorkOnTask component
        entity->removeComponent<WorkOnTaskComponent>();
        return;
    }

    TaskComponent *const cmptTask = taskEntity->getComponent<TaskComponent>();
    if (!cmptTask)
    {
        // If this WorkOnTask component refers to an entity that doesn't have a task, delete the WorkOnTask component
        entity->removeComponent<WorkOnTaskComponent>();
        return;
    }

    const PositionComponent *const cmptPositionEntity = entity->getComponent<PositionComponent>();
    const PositionComponent *const cmptPositionTask = taskEntity->getComponent<PositionComponent>();
    if (!cmptPositionEntity || !cmptPositionTask)
        return;

    const TileCoordinates entityPosition = cmptPositionEntity->getPosition();
    const TileCoordinates taskPosition = cmptPositionTask->getPosition();

    // If the entity is not in range to work on the task, wait until it is closer
    if (PathFinding::euclideanDistance(entityPosition, taskPosition) > 1.5)
    {
        if (!entity->hasComponent<MoveComponent>())
        {
            entity->addComponent(std::make_unique<MoveComponent>(taskPosition, false));
        }

        return;
    }

    --(cmptTask->workRemaining); // Entity is in range of the task - do one unit of work

    if (cmptTask->workRemaining == 0)
    {
        cmptTask->onCompletion();
        taskEntity->removeComponent<TaskComponent>();
        entity->removeComponent<WorkOnTaskComponent>();
    }
}
