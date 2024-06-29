#ifndef TILE_COMPONENT_H_
#define TILE_COMPONENT_H_

#include "components/Component.hpp"
#include "game/TileProperty.hpp"

/**
 * Indicates that the entity is a Tile. A tile is effectively a position in the district.
 * Tiles have properties which affect how they appear in the UI, and how other Entities interact with them.
 */
struct TileComponent : public Component
{
    TileComponent(TileProperty::TileProperty property) : property(property) {}

    virtual ~TileComponent() = default;

    TileProperty::TileProperty property;
};

#endif /* TILE_COMPONENT_H_ */
