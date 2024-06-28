#ifndef CITIZENSYSTEM_H_
#define CITIZENSYSTEM_H_

#include "gamesystems/GameSystem.hpp"

class CitizenSystem : public GameSystem
{
public:
    CitizenSystem();
    virtual ~CitizenSystem();

protected:
    virtual void processEntity(District *, const std::unique_ptr<Entity> &) override;
};

#endif /* CITIZENSYSTEM_H_ */
