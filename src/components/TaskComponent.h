#ifndef TASK_COMPONENT_H_
#define TASK_COMPONENT_H_

#include "components/Component.h"
#include <functional>

struct TaskComponent : public Component
{
    TaskComponent(int work, std::function<void()> onCompletion)
        : workRemaining(work), onCompletion(onCompletion) {}

    virtual ~TaskComponent() = default;

    unsigned int workRemaining;
    std::function<void()> onCompletion;
};

#endif /* TASK_COMPONENT_H_ */
