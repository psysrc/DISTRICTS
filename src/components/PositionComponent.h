#ifndef POSITIONCOMPONENT_H_
#define POSITIONCOMPONENT_H_

#include "components/Component.h"
#include "game/TileCoordinates.h"

struct PositionComponent : public Component
{
    PositionComponent(TileCoordinates coords) : position(coords) {}

    virtual ~PositionComponent() = default;

    TileCoordinates position;
};

#endif /* POSITIONCOMPONENT_H_ */
