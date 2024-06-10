#ifndef WALKSYSTEM_H_
#define WALKSYSTEM_H_

#include "gamesystems/GameSystem.h"

class WalkSystem : public GameSystem
{
public:
    WalkSystem();
    virtual ~WalkSystem();
    virtual void run(District *pDistrict) override;
};

#endif /* WALKSYSTEM_H_ */
