#include "OccupyRules.h"

#include "entities/Entity.h"
#include "game/Tile.h"
#include "deprecated/TileHelpers.h"
#include "components/TileComponent.h"

bool OccupyRules::canOccupy(District *pDistrict, Entity *pEntity, Tile *pTile)
{
    if (!pEntity || !pTile)
        return false;

    if (deprecatedGetTileEntity(pDistrict, pTile)->getComponent<TileComponent>()->property == TileProperty::Water)
    {
        return false;
    }

    if (pTile->getEntity() != nullptr)
        return false;

    return true;
}
