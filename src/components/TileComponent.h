#ifndef TILE_COMPONENT_H_
#define TILE_COMPONENT_H_

#include "components/Component.h"

struct TileComponent : public Component
{
    TileComponent(){}

    virtual ~TileComponent() = default;

    int renderColour;
};

#endif /* TILE_COMPONENT_H_ */
