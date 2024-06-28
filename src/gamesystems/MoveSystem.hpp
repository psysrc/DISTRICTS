#ifndef MOVESYSTEM_H_
#define MOVESYSTEM_H_

#include "gamesystems/GameSystem.hpp"

class MoveSystem : public GameSystem
{
public:
    MoveSystem();
    virtual ~MoveSystem();
    virtual void run(District *pDistrict) override;
};

#endif /* MOVESYSTEM_H_ */
