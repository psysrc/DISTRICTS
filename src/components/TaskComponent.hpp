#ifndef TASK_COMPONENT_H_
#define TASK_COMPONENT_H_

#include "components/Component.hpp"
#include <functional>
#include "game/TaskLookup.hpp"
#include "entities/Entity.hpp"

/**
 * Specifies a task (i.e. an activity) that can be worked on in a district.
 * Typically, a task will take a certain amount of time to complete.
 * Once the task is done, an arbitrary action can take place.
 */
struct TaskComponent : public Component
{
    static TaskLookup* taskLookup;

    TaskComponent(Entity* entity, int work, std::function<void()> onCompletion);

    virtual ~TaskComponent();

    unsigned int workRemaining;
    std::function<void()> onCompletion;

private:
    void registerLookup();
    void unregisterLookup();

    Entity* const entity;
};

#endif /* TASK_COMPONENT_H_ */
