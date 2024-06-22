#include "OccupyRules.h"

#include "entities/Entity.h"
#include "game/Tile.h"
#include "deprecated/TileHelpers.h"
#include "components/TileComponent.h"
#include "components/PositionComponent.h"
#include "game/District.h"
#include "components/OccupySpaceComponent.h"
#include <algorithm>

bool OccupyRules::canOccupy(District *pDistrict, Entity *pEntity, DeprecatedTile *pTile)
{
    if (!pEntity || !pTile)
        return false;

    if (deprecatedGetTileEntity(pDistrict, pTile)->getComponent<TileComponent>()->property == TileProperty::Water)
    {
        return false;
    }

    const auto& entities = pDistrict->entitiesAtPosition(pTile->getCoordinates());
    if (std::find_if(entities.begin(), entities.end(), [](Entity* e) { return e->hasComponent<OccupySpaceComponent>(); }) != entities.end())
    {
        return false;
    }


    return true;
}
