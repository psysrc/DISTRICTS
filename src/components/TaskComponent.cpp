#include "components/TaskComponent.h"

TaskComponent::TaskComponent(Entity* entity, int work, std::function<void()> onCompletion)
    : workRemaining(work), onCompletion(onCompletion), entity(entity)
{
    registerLookup();
}

TaskComponent::~TaskComponent()
{
    unregisterLookup();
}

void TaskComponent::registerLookup()
{
    if (taskLookup == nullptr)
    {
        throw std::runtime_error("Failed to register TaskComponent: TaskLookup is null");
    }

    taskLookup->push_back(entity);
}

void TaskComponent::unregisterLookup()
{
    if (taskLookup != nullptr)
    {
        const auto it = std::find_if(taskLookup->begin(), taskLookup->end(), [this](const Entity* e){return e == entity;});

        if (it != taskLookup->end())
        {
            taskLookup->erase(it);
        }
    }
}

TaskLookup* TaskComponent::taskLookup = nullptr;
