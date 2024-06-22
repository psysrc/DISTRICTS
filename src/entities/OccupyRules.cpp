#include "OccupyRules.h"

#include "entities/Entity.h"
#include "game/Tile.h"
#include "deprecated/TileProperty.h"

bool OccupyRules::canOccupy(District *pDistrict, Entity *pEntity, Tile *pTile)
{
    if (!pEntity || !pTile)
        return false;

    if (deprecatedGetProperty(pDistrict, pTile) == TileProperty::Water)
    {
        return false;
    }

    if (pTile->getEntity() != nullptr)
        return false;

    return true;
}
