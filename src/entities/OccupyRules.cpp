#include "OccupyRules.h"

#include "entities/Entity.h"
#include "game/TileCoordinates.h"
#include "components/TileComponent.h"
#include "components/PositionComponent.h"
#include "game/District.h"
#include "components/OccupySpaceComponent.h"
#include <algorithm>

bool OccupyRules::canOccupy(District *district, const Entity *tile)
{
    if (!tile)
        return false;

    if (tile->getComponent<TileComponent>()->property == TileProperty::Water)
    {
        return false;
    }

    const auto& entities = district->entitiesAtPosition(tile->getComponent<PositionComponent>()->getPosition());
    if (std::find_if(entities.begin(), entities.end(), [](Entity* e) { return e->hasComponent<OccupySpaceComponent>(); }) != entities.end())
    {
        return false;
    }

    return true;
}

bool OccupyRules::canOccupy(District * district, TileCoordinates coordinates)
{
    const auto& entities = district->entitiesAtPosition(coordinates);
    const auto it = std::find_if(entities.begin(), entities.end(), [](Entity* e){ return e->hasComponent<TileComponent>(); });

    return canOccupy(district, *it);
}
