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

    void setPosition(TileCoordinates);
    TileCoordinates getPosition() const;

private:
    void registerLookup();
    void unregisterLookup();

    TileCoordinates position;
    Entity* const entity;
};

#endif /* POSITION_COMPONENT_H_ */
