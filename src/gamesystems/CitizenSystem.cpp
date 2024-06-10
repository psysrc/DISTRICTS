#include "gamesystems/CitizenSystem.h"

#include <memory>
#include "game/District.h"
#include "components/CitizenComponent.h"
#include "components/WalkComponent.h"
#include "components/WorkerComponent.h"

CitizenSystem::CitizenSystem() {}

CitizenSystem::~CitizenSystem() {}

void CitizenSystem::run(District *pDistrict)
{
    for (const std::unique_ptr<Entity> &upEntity : pDistrict->getEntities())
    {
        CitizenComponent *pCitC = upEntity->getComponent<CitizenComponent>();
        WalkComponent *pWlkC = upEntity->getComponent<WalkComponent>();
        WorkerComponent *pWrkC = upEntity->getComponent<WorkerComponent>();

        if (pCitC != nullptr && pWlkC != nullptr && pWrkC != nullptr)
        {
            // Get a new task if this citizen has none
            if (!pWrkC->wpCurrentTask.lock())
            {
                pWrkC->wpCurrentTask = pDistrict->getOldestTask();
            }

            if (!pWlkC->pDestination)
            {
                if (std::shared_ptr<Tasks::Task> spCurrentTask = pWrkC->wpCurrentTask.lock())
                {
                    // If citizen has no destination but has a task, set destination to its current task
                    pWlkC->pDestination = spCurrentTask->getTile();
                }
            }
        }
    }
}
