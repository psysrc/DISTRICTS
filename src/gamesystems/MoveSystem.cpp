#include "gamesystems/MoveSystem.h"

#include "game/District.h"
#include "components/PositionComponent.h"
#include "components/MoveComponent.h"
#include "entities/OccupyRules.h"

MoveSystem::MoveSystem() {}

MoveSystem::~MoveSystem() {}

void MoveSystem::run(District *pDistrict)
{
    for (const std::unique_ptr<Entity> &entity : pDistrict->getEntities())
    {
        MoveComponent *cmptMove = entity->getComponent<MoveComponent>();
        if (!cmptMove)
            continue;

        PositionComponent *cmptPosition = entity->getComponent<PositionComponent>();
        if (!cmptPosition)
            continue;

        if (cmptPosition->getPosition() != cmptMove->destination)
        {
            // Initial debug implementation to prove the concept

            if (OccupyRules::canOccupy(pDistrict, cmptMove->destination))
            {
                cmptPosition->setPosition(cmptMove->destination);
            }
        }

        entity->removeComponent<MoveComponent>();
    }
}
