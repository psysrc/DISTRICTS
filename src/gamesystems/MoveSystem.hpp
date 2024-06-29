#ifndef MOVESYSTEM_H_
#define MOVESYSTEM_H_

#include "gamesystems/GameSystem.hpp"

/**
 * Handles the movement of entities.
 */
class MoveSystem : public GameSystem
{
public:
    MoveSystem();
    virtual ~MoveSystem();

protected:
    virtual void processEntity(District *, const std::unique_ptr<Entity> &) override;
};

#endif /* MOVESYSTEM_H_ */
