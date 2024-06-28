#include "OccupyRules.hpp"

#include "entities/Entity.hpp"
#include "game/TileCoordinates.hpp"
#include "components/TileComponent.hpp"
#include "components/PositionComponent.hpp"
#include "game/District.hpp"
#include "components/OccupySpaceComponent.hpp"
#include <algorithm>

bool OccupyRules::canOccupy(District *district, const Entity *tile)
{
    if (!tile)
        return false;

    if (tile->getComponent<TileComponent>()->property == TileProperty::Water)
    {
        return false;
    }

    const auto& entities = district->getEntitiesAtPosition(tile->getComponent<PositionComponent>()->getPosition());
    if (std::find_if(entities.begin(), entities.end(), [](Entity* e) { return e->hasComponent<OccupySpaceComponent>(); }) != entities.end())
    {
        return false;
    }

    return true;
}

bool OccupyRules::canOccupy(District * district, TileCoordinates coordinates)
{
    const auto& entities = district->getEntitiesAtPosition(coordinates);
    const auto it = std::find_if(entities.begin(), entities.end(), [](Entity* e){ return e->hasComponent<TileComponent>(); });

    return canOccupy(district, *it);
}
