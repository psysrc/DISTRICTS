#include "gamesystems/WorkSystem.h"

#include <memory>
#include "entities/Entity.h"
#include "game/District.h"
#include "components/WorkerComponent.h"

WorkSystem::WorkSystem() {}

WorkSystem::~WorkSystem() {}

void WorkSystem::run(District* pDistrict) {
    for (const std::unique_ptr<Entity>& entity : pDistrict->getEntities())
    {
        WorkerComponent* wc = entity->getComponent<WorkerComponent>();
		if (wc != nullptr && wc->working)
        {
            if (auto spCurrentTask = wc->wpCurrentTask.lock())
            {
                // TODO
                // Need to check if the entity is in range of the task
                // If so, work on the task and handle things from there
            }
            else
            {
                wc->wpCurrentTask.reset();
            }
        }
    }
}