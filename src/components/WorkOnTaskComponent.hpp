#ifndef WORK_ON_TASK_COMPONENT_H_
#define WORK_ON_TASK_COMPONENT_H_

#include "components/Component.hpp"
#include "game/ID.hpp"

struct WorkOnTaskComponent : public Component
{
    WorkOnTaskComponent(ID_t id) : entityID(id) {}

    virtual ~WorkOnTaskComponent() = default;

    ID_t entityID;
};

#endif /* WORK_ON_TASK_COMPONENT_H_ */
