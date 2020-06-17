#ifndef GROWSYSTEM_H_
#define GROWSYSTEM_H_

#include "gamesystems/GameSystem.h"

class GrowSystem : public GameSystem {
public:
    GrowSystem();
    virtual ~GrowSystem();
    virtual void run(District* pDistrict) override;
};

#endif /* GROWSYSTEM_H_ */