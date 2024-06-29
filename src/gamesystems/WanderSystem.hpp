#ifndef WANDER_SYSTEM_H_
#define WANDER_SYSTEM_H_

#include "gamesystems/GameSystem.hpp"

/**
 * Handles the logic to make entities randomly wander around the district.
 */
class WanderSystem : public GameSystem
{
public:
    WanderSystem();
    virtual ~WanderSystem();

protected:
    virtual void processEntity(District *, const std::unique_ptr<Entity> &) override;
};

#endif /* WANDER_SYSTEM_H_ */
