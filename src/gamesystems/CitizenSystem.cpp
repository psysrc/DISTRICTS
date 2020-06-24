#include "gamesystems/CitizenSystem.h"

#include <memory>
#include "game/District.h"
#include "components/CitizenComponent.h"
#include "components/WalkComponent.h"
#include "components/WorkerComponent.h"

CitizenSystem::CitizenSystem() {}

CitizenSystem::~CitizenSystem() {}

void CitizenSystem::run(District* pDistrict) {
    for (const std::unique_ptr<Entity>& entity : pDistrict->getEntities())
	{
		CitizenComponent* cznC = entity->getComponent<CitizenComponent>();
        WalkComponent* wlkC = entity->getComponent<WalkComponent>();
        WorkerComponent* wrkC = entity->getComponent<WorkerComponent>();
        
		if (cznC != nullptr && wlkC != nullptr && wrkC != nullptr)
        {
            // Get a new task if this citizen has none
            if (!wrkC->wpCurrentTask.lock())
            {
                wrkC->wpCurrentTask = pDistrict->getOldestTask();
            }

            if (!wlkC->destination)
            {
                if (std::shared_ptr<Tasks::Task> spCurrentTask = wrkC->wpCurrentTask.lock())
                {
                    // If citizen has no destination but has a task, set destination to its current task
                    wlkC->destination = spCurrentTask->getTile();
                }
            }
        }
    }
}