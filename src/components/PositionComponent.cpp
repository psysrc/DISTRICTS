#include "components/PositionComponent.h"

#include "game/District.h"

Tile* PositionComponent::getTile() const { return tile; }
int PositionComponent::getX() const { return x; }
int PositionComponent::getY() const { return y; }

void PositionComponent::setTile(Tile* pTile) {
    tile = pTile;
    x = tile->getX();
    y = tile->getY();
}