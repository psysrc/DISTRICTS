#ifndef CITIZENSYSTEM_H_
#define CITIZENSYSTEM_H_

#include "gamesystems/GameSystem.h"

class CitizenSystem : public GameSystem
{
public:
    CitizenSystem();
    virtual ~CitizenSystem();
    virtual void run(District *pDistrict) override;
};

#endif /* CITIZENSYSTEM_H_ */
