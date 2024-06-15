#include "entities/Tree.h"

#include "components/PositionComponent.h"
#include "components/DrawComponent.h"
#include "components/CanBeCutDownComponent.h"

std::unique_ptr<Entity> makeTree(TileCoordinates coords)
{
    std::unique_ptr<Entity> entity = std::make_unique<Entity>("Tree");

    entity->addComponent(std::make_unique<PositionComponent>(coords));
    entity->addComponent(std::make_unique<CanBeCutDownComponent>());
    entity->addComponent(std::make_unique<DrawComponent>('$'));

    return entity;
}
