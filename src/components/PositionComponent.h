#ifndef POSITIONCOMPONENT_H_
#define POSITIONCOMPONENT_H_

#include "components/Component.h"
#include "game/TileCoordinates.h"

struct PositionComponent : public Component
{
    PositionComponent(TileCoordinates coords)
        : nextCoordinates(coords), currentCoordinates(-1, -1), couldNotMove(false) {}

    virtual ~PositionComponent() = default;

    TileCoordinates nextCoordinates;
    TileCoordinates currentCoordinates;
    bool couldNotMove;
};

#endif /* POSITIONCOMPONENT_H_ */
