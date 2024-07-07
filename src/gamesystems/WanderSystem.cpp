#include "gamesystems/WanderSystem.hpp"

#include "game/District.hpp"
#include "entities/Entity.hpp"
#include "components/RandomWanderComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/MoveComponent.hpp"
#include "pathfinding/PathFinding.hpp"
#include "entities/OccupyRules.hpp"
#include <optional>

WanderSystem::WanderSystem() {}

WanderSystem::~WanderSystem() {}

unsigned int generateNewRandomWaitTime(RandomWanderComponent *cmptWander)
{
    return cmptWander->minTicksToWait + (rand() % (cmptWander->maxTicksToWait - cmptWander->minTicksToWait + 1));
}

std::optional<TileCoordinates> generateNewRandomAccessibleLocation(District *district, Entity *entity, TileCoordinates position)
{
    constexpr unsigned int maxAttempts = 10;
    unsigned int numAttempts = 0;

    std::optional<TileCoordinates> potentialDestination;

    while (numAttempts < maxAttempts)
    {
        ++numAttempts;

        const TileCoordinates destination(rand() % District::districtSize, rand() % District::districtSize);

        if (OccupyRules::canOccupy(district, entity, destination))
        {
            if (PathFinding::findPath(district, entity, position, destination, true))
            {
                potentialDestination = destination;
                break;
            }
        }
    }

    return potentialDestination;
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
        cmptWander->ticksLeftToWait = generateNewRandomWaitTime(cmptWander);

        const auto possibleDestination = generateNewRandomAccessibleLocation(district, entity.get(), cmptPosition->getPosition());
        if (possibleDestination.has_value())
        {
            entity->addComponent(std::make_unique<MoveComponent>(possibleDestination.value(), false));
        }
    }
}
