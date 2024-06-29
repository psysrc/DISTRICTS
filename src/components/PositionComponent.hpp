#ifndef POSITION_COMPONENT_H_
#define POSITION_COMPONENT_H_

#include "components/Component.hpp"
#include "game/TileCoordinates.hpp"
#include "game/PositionLookup.hpp"

/**
 *  If an entity exists in physical space and has a well defined location, it will have a `PositionComponent`.
 */
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
