#include "components/PositionComponent.h"

#include "game/District.h"

Tile* PositionComponent::getTile() const { return tile; }
int PositionComponent::getX() const { return x; }
int PositionComponent::getY() const { return y; }

void PositionComponent::setTile(Tile* pTile) {
    tile = pTile;

    if (tile == nullptr)
    {
        x = -1;
        y = -1;
    }
    else
    {
        x = tile->getX();
        y = tile->getY();
    }
}