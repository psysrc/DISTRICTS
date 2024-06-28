#include "gamesystems/CitizenSystem.hpp"

#include <memory>
#include "game/District.hpp"
#include "components/CitizenComponent.hpp"
#include "components/WorkOnTaskComponent.hpp"

CitizenSystem::CitizenSystem() {}

CitizenSystem::~CitizenSystem() {}

void CitizenSystem::processEntity(District *district, const std::unique_ptr<Entity> &entity)
{
    CitizenComponent *cmptCitizen = entity->getComponent<CitizenComponent>();
    if (!cmptCitizen)
        return;

    // If the citizen is already working on a task then ignore it
    if (entity->hasComponent<WorkOnTaskComponent>())
        return;

    const auto &districtTasks = district->getTasks();

    // If the district has no tasks, there is nothing the Citizen can do
    if (districtTasks.empty())
        return;

    // Set the Citizen going with the task
    const auto taskEntity = *(districtTasks.begin());
    entity->addComponent(std::make_unique<WorkOnTaskComponent>(taskEntity->getID()));
}
