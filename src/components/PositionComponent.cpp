#include "components/PositionComponent.h"

#include "game/District.h"

PositionComponent::PositionComponent(Entity* pEntity/*Deprecated*/) :
    entity(pEntity/*Deprecated*/), tile(nullptr), x(-1), y(-1) {}

PositionComponent::~PositionComponent() {}

Tile* PositionComponent::getTile() const { return tile; }

int PositionComponent::getX() const { return x; }

int PositionComponent::getY() const { return y; }

void PositionComponent::setTile(Tile* pTile) {
    if (tile != nullptr)
        tile->vacateEntity();   // Deprecated behaviour

    tile = pTile;

    if (tile == nullptr)
    {
        x = -1;
        y = -1;
    }
    else
    {
        tile->vacateEntity();   // Deprecated behaviour
        tile->occupy(entity);   // Deprecated behaviour
        x = tile->getX();
        y = tile->getY();
    }
}