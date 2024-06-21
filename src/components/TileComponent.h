#ifndef TILE_COMPONENT_H_
#define TILE_COMPONENT_H_

#include "components/Component.h"
#include "ui/TileColours.h"

struct TileComponent : public Component
{
    TileComponent(){}

    virtual ~TileComponent() = default;

    int renderColour = COLOUR_UNKNOWN;
};

#endif /* TILE_COMPONENT_H_ */
