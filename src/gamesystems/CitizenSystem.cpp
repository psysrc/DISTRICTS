#include "gamesystems/CitizenSystem.h"

#include <memory>
#include "game/District.h"
#include "components/CitizenComponent.h"
#include <components/WorkOnTaskComponent.h>

CitizenSystem::CitizenSystem() {}

CitizenSystem::~CitizenSystem() {}

void CitizenSystem::run(District * district)
{
    for (const std::unique_ptr<Entity> &entity : district->getEntities())
    {
        CitizenComponent *cmptCitizen = entity->getComponent<CitizenComponent>();
        if (!cmptCitizen)
            continue;

        // If the citizen is already working on a task then ignore it
        if (entity->hasComponent<WorkOnTaskComponent>())
            continue;

        const auto& districtTasks = district->getTasks();

        // If the district has no tasks, there is nothing the Citizen can do
        if (districtTasks.empty())
            continue;

        // Set the Citizen going with the task
        const auto taskEntity = *(districtTasks.begin());
        entity->addComponent(std::make_unique<WorkOnTaskComponent>(taskEntity->getID()));
    }
}
