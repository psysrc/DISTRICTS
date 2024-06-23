#ifndef WORKERCOMPONENT_H_
#define WORKERCOMPONENT_H_

#include "components/Component.h"
#include <memory>

struct WorkerComponent : public Component
{
    WorkerComponent() {}

    virtual ~WorkerComponent() = default;

    bool working;
    // std::weak_ptr<Tasks::DeprecatedTask> wpCurrentTask;

};

#endif /* WORKERCOMPONENT_H_ */
