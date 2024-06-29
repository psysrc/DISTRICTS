#ifndef GAMESYSTEM_H_
#define GAMESYSTEM_H_

#include <memory>

class District;
class Entity;

/**
 * Base class for all GameSystems in the DISTRICTS ECS (Entity Component System).
 * GameSystems contain the core logic of the game, and act upon Components that are attached to Entities.
 */
class GameSystem
{
public:
    GameSystem();
    virtual ~GameSystem();
    virtual void run(District *);

protected:
    virtual void processEntity(District *, const std::unique_ptr<Entity> &);
};

#endif /* GAMESYSTEM_H_ */
