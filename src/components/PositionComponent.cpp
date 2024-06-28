#include "components/PositionComponent.hpp"

PositionComponent::PositionComponent(TileCoordinates coords, Entity* entity) : position(coords), entity(entity)
{
    registerLookup();
}

PositionComponent::~PositionComponent()
{
    unregisterLookup();
}

void PositionComponent::setPosition(TileCoordinates newPosition)
{
    unregisterLookup();
    position = newPosition;
    registerLookup();
}

TileCoordinates PositionComponent::getPosition() const
{
    return position;
}

void PositionComponent::registerLookup()
{
    if (positionLookup == nullptr)
    {
        throw std::runtime_error("Failed to register PositionComponent: PositionLookup is null");
    }

    (*positionLookup)[position].insert(entity);
}

void PositionComponent::unregisterLookup()
{
    if (positionLookup != nullptr)
    {
        (*positionLookup)[position].erase(entity);
    }
}

PositionLookup* PositionComponent::positionLookup = nullptr;
