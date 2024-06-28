#ifndef TASK_COMPONENT_H_
#define TASK_COMPONENT_H_

#include "components/Component.h"
#include <functional>
#include "game/TaskLookup.h"
#include "entities/Entity.h"

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
