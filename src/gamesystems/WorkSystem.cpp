#include "gamesystems/WorkSystem.h"

#include <memory>
#include "entities/Entity.h"
#include "game/District.h"
#include "components/WorkerComponent.h"
#include "components/PositionComponent.h"
#include "pathfinding/PathFinding.h"

WorkSystem::WorkSystem() {}

WorkSystem::~WorkSystem() {}

void WorkSystem::run(District *pDistrict)
{
    for (const std::unique_ptr<Entity> &upEntity : pDistrict->getEntities())
    {
        WorkerComponent *pWC = upEntity->getComponent<WorkerComponent>();
        PositionComponent *pPC = upEntity->getComponent<PositionComponent>();

        if (pWC != nullptr && pWC->working && pPC != nullptr)
        {
            // If the worker's current task exists (isn't empty and hasn't been deleted by the district)
            if (auto spCurrentTask = pWC->wpCurrentTask.lock())
            {
                // Check if the entity is within range to work on the task
                if (PathFinding::euclideanDistance(pDistrict->getTile(pPC->getPosition()), spCurrentTask->getTile()) < 1.5)
                {
                    spCurrentTask->workOn(pDistrict);
                }

                // If the task has been completed, it can be removed from the district and this worker can clear its current task
                if (spCurrentTask->isCompleted())
                {
                    pDistrict->deleteTask(spCurrentTask.get());
                    pWC->wpCurrentTask.reset();
                }
            }
            else
            {
                // Clear the current task for this worker in case it has been deleted from the district
                pWC->wpCurrentTask.reset();
            }
        }
    }
}
