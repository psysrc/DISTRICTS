#ifndef GAMESYSTEM_H_
#define GAMESYSTEM_H_

#include <memory>

class District;
class Entity;

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
