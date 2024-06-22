#include "deprecated/TileProperty.h"
#include <algorithm>
#include "game/District.h"
#include "game/Tile.h"
#include "components/TileComponent.h"

TileProperty::TileProperty deprecatedGetProperty(District* district, Tile* tile)
{
    const auto& entities = district->entitiesAtPosition(tile->getCoordinates());

    const auto it = std::find_if(entities.begin(), entities.end(), [](Entity* e)
    {
        return e->hasComponent<TileComponent>();
    });

    if (it == entities.end())
    {
        throw std::runtime_error("Couldn't find an entity with TileComponent at a location");
    }

    return (*it)->getComponent<TileComponent>()->property;
}
