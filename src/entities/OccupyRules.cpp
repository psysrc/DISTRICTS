#include "OccupyRules.h"

#include "entities/Entity.h"
#include "game/Tile.h"

bool OccupyRules::canOccupy(Entity *pEntity, Tile *pTile)
{
    if (!pEntity || !pTile)
        return false;

    if (pTile->getProperty() == TileProperty::Water)
        return false;

    if (pTile->getEntity() != nullptr)
        return false;

    return true;
}
