#ifndef GROWSYSTEM_H_
#define GROWSYSTEM_H_

#include "gamesystems/GameSystem.hpp"

class GrowSystem : public GameSystem
{
public:
    GrowSystem();
    virtual ~GrowSystem();

protected:
    virtual void processEntity(District *, const std::unique_ptr<Entity> &) override;
};

#endif /* GROWSYSTEM_H_ */
