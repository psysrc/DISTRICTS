#ifndef POSITION_COMPONENT_H_
#define POSITION_COMPONENT_H_

#include "components/Component.h"
#include "game/TileCoordinates.h"
#include "game/PositionLookup.h"

struct PositionComponent : public Component
{
    static PositionLookup* positionLookup;

    PositionComponent(TileCoordinates coords, Entity* entity);

    virtual ~PositionComponent();

    TileCoordinates position;  // TODO: Needs to be private with getters/setters in case it gets updated

private:
    Entity* const entity;
};

#endif /* POSITION_COMPONENT_H_ */
