#include "gamesystems/WanderSystem.hpp"

#include "game/District.hpp"
#include "entities/Entity.hpp"
#include "components/RandomWanderComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/MoveComponent.hpp"
#include "pathfinding/PathFinding.hpp"

WanderSystem::WanderSystem() {}

WanderSystem::~WanderSystem() {}

unsigned int generateNewRandomWaitTime(RandomWanderComponent *cmptWander)
{
    return cmptWander->minTicksToWait + (rand() % (cmptWander->maxTicksToWait - cmptWander->minTicksToWait + 1));
}

TileCoordinates generateNewRandomAccessibleLocation(District *district, Entity *entity, TileCoordinates position)
{
    TileCoordinates destination(-1, -1);

    do // Keep choosing random tiles until one is found which the entity can move to
    {
        destination.x = rand() % District::districtSize;
        destination.y = rand() % District::districtSize;

    } while (!PathFinding::findPath(district, entity, position, destination, false));

    return destination;
}

void WanderSystem::processEntity(District *district, const std::unique_ptr<Entity> &entity)
{
    RandomWanderComponent *cmptWander = entity->getComponent<RandomWanderComponent>();
    if (!cmptWander)
        return;

    PositionComponent *cmptPosition = entity->getComponent<PositionComponent>();
    if (!cmptPosition)
        return;

    // Ignore entities that are already wandering around
    if (entity->hasComponent<MoveComponent>())
        return;

    if (cmptWander->ticksLeftToWait > 0)
    {
        --(cmptWander->ticksLeftToWait);
    }
    else
    {
        const TileCoordinates destination = generateNewRandomAccessibleLocation(district, entity.get(), cmptPosition->getPosition());
        entity->addComponent(std::make_unique<MoveComponent>(destination, false));

        cmptWander->ticksLeftToWait = generateNewRandomWaitTime(cmptWander);
    }
}
