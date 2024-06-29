#ifndef CITIZENSYSTEM_H_
#define CITIZENSYSTEM_H_

#include "gamesystems/GameSystem.hpp"

/**
 * Controls the logic for all Citizens in the district.
 * For example, some citizens might go look for work to do in the district, or go eat food, etc.
 */
class CitizenSystem : public GameSystem
{
public:
    CitizenSystem();
    virtual ~CitizenSystem();

protected:
    virtual void processEntity(District *, const std::unique_ptr<Entity> &) override;
};

#endif /* CITIZENSYSTEM_H_ */
