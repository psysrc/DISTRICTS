#ifndef WANDER_SYSTEM_H_
#define WANDER_SYSTEM_H_

#include "gamesystems/GameSystem.hpp"

class WanderSystem : public GameSystem
{
public:
    WanderSystem();
    virtual ~WanderSystem();
    virtual void run(District *pDistrict) override;
};

#endif /* WANDER_SYSTEM_H_ */
