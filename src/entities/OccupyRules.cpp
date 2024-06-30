#include "entities/OccupyRules.hpp"

#include "entities/Entity.hpp"
#include "game/TileCoordinates.hpp"
#include "components/TileComponent.hpp"
#include "components/PositionComponent.hpp"
#include "game/District.hpp"
#include "components/OccupySpaceComponent.hpp"
#include <algorithm>
#include "components/AcquaticComponent.hpp"
#include "components/TerrestrialComponent.hpp"

bool OccupyRules::canOccupy(District *district, const Entity* entity, const Entity *tile)
{
    if (!tile)
        return false;

    const TileComponent* cmptTile = tile->getComponent<TileComponent>();
    if (!cmptTile)
        throw std::runtime_error("OccupyRules: Tile entity does not have a TileComponent");

    if (cmptTile->property != TileProperty::Water && !entity->hasComponent<TerrestrialComponent>())
        return false;

    if (cmptTile->property == TileProperty::Water && !entity->hasComponent<AcquaticComponent>())
        return false;

    const auto& entities = district->getEntitiesAtPosition(tile->getComponent<PositionComponent>()->getPosition());
    if (std::find_if(entities.begin(), entities.end(), [](Entity* e) { return e->hasComponent<OccupySpaceComponent>(); }) != entities.end())
        return false;

    return true;
}

bool OccupyRules::canOccupy(District * district, const Entity* entity, TileCoordinates coordinates)
{
    const auto& entities = district->getEntitiesAtPosition(coordinates);
    const auto it = std::find_if(entities.begin(), entities.end(), [](Entity* e){ return e->hasComponent<TileComponent>(); });

    return canOccupy(district, entity, *it);
}
