#include "gamesystems/GameSystem.hpp"

#include "game/District.hpp"

GameSystem::GameSystem() {}

GameSystem::~GameSystem() {}

void GameSystem::run(District *district)
{
    for (const std::unique_ptr<Entity> &entity : district->getEntities())
    {
        processEntity(district, entity);
    }
}

void GameSystem::processEntity(District *, const std::unique_ptr<Entity> &)
{

}
