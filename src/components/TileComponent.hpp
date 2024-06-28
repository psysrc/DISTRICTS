#ifndef TILE_COMPONENT_H_
#define TILE_COMPONENT_H_

#include "components/Component.hpp"
#include "game/TileProperty.hpp"

struct TileComponent : public Component
{
    TileComponent(TileProperty::TileProperty property) : property(property) {}

    virtual ~TileComponent() = default;

    TileProperty::TileProperty property;
};

#endif /* TILE_COMPONENT_H_ */
