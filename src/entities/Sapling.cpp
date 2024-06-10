#include "entities/Sapling.h"

#include "components/GrowComponent.h"
#include "components/PositionComponent.h"
#include "components/DrawComponent.h"

constexpr int maxSecondsToGrow = 6 * 60;
constexpr int minSecondsToGrow = 2 * 60;

std::unique_ptr<Entity> makeSapling(TileCoordinates coords)
{
    std::unique_ptr<Entity> entity = std::make_unique<Entity>("Tree Sapling");

    int seconds = minSecondsToGrow + (rand() % (maxSecondsToGrow - minSecondsToGrow + 1));

    entity->addComponent<GrowComponent>(seconds);
    entity->addComponent<PositionComponent>(coords);
    entity->addComponent<DrawComponent>(',');

    return entity;
}
