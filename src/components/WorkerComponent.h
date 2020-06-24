#ifndef WORKERCOMPONENT_H_
#define WORKERCOMPONENT_H_

#include "components/Component.h"
#include <memory>
#include "tasks/Task.h"

class WorkerComponent : public Component {
public:
    WorkerComponent() {}
    virtual ~WorkerComponent() {}

    bool working;
    std::weak_ptr<Tasks::Task> wpCurrentTask;
};

#endif /* WORKERCOMPONENT_H_ */