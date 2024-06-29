#ifndef WORKSYSTEM_H_
#define WORKSYSTEM_H_

#include "gamesystems/GameSystem.hpp"

/**
 * Manages entities that want to work on a task.
 */
class WorkSystem : public GameSystem
{
public:
    WorkSystem();
    virtual ~WorkSystem();

protected:
    virtual void processEntity(District *, const std::unique_ptr<Entity> &) override;
};

#endif /* WORKSYSTEM_H_ */
