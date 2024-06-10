#ifndef WORKSYSTEM_H_
#define WORKSYSTEM_H_

#include "gamesystems/GameSystem.h"

class WorkSystem : public GameSystem
{
public:
    WorkSystem();
    virtual ~WorkSystem();
    virtual void run(District *pDistrict) override;
};

#endif /* WORKSYSTEM_H_ */
