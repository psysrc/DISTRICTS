#include "gamesystems/WanderSystem.hpp"

#include "game/District.hpp"
#include "entities/Entity.hpp"
#include "components/RandomWanderComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/MoveComponent.hpp"
#include "pathfinding/PathFinding.hpp"

WanderSystem::WanderSystem() {}

WanderSystem::~WanderSystem() {}

unsigned int generateNewRandomWaitTime(RandomWanderComponent* cmptWander)
{
    return cmptWander->minTicksToWait + (rand() % (cmptWander->maxTicksToWait - cmptWander->minTicksToWait + 1));
}

TileCoordinates generateNewRandomAccessibleLocation(District* district, Entity* entity, TileCoordinates position)
{
    TileCoordinates destination;

    do  // Keep choosing random tiles until one is found which the entity can move to
    {
        destination.x = rand() % District::districtSize;
        destination.y = rand() % District::districtSize;

    } while (!PathFinding::findPath(district, entity, position, destination, false));

    return destination;
}

void WanderSystem::run(District *district)
{
    for (const auto &entity : district->getEntities())
    {
        RandomWanderComponent *cmptWander = entity->getComponent<RandomWanderComponent>();
        if (!cmptWander)
            continue;

        PositionComponent *cmptPosition = entity->getComponent<PositionComponent>();
        if (!cmptPosition)
            continue;

        // Ignore entities that are already wandering around
        if (entity->hasComponent<MoveComponent>())
            continue;

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
}
