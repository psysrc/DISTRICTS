#include "components/PositionComponent.h"

PositionComponent::PositionComponent(TileCoordinates coords, Entity* entity) : position(coords), entity(entity)
{
    if (positionLookup == nullptr)
    {
        throw std::runtime_error("Failed to create PositionComponent: PositionLookup is null");
    }

    (*positionLookup)[position].insert(entity);
}

PositionComponent::~PositionComponent()
{
    if (positionLookup != nullptr)
    {
        (*positionLookup)[position].erase(entity);
    }
}

PositionLookup* PositionComponent::positionLookup = nullptr;
