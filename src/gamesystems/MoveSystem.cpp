#include "gamesystems/MoveSystem.h"

#include "game/District.h"
#include "components/PositionComponent.h"
#include "entities/OccupyRules.h"

MoveSystem::MoveSystem() {}

MoveSystem::~MoveSystem() {}

void MoveSystem::run(District *pDistrict)
{
    for (const std::unique_ptr<Entity> &upEntity : pDistrict->getEntities())
    {
        PositionComponent *pPC = upEntity->getComponent<PositionComponent>();
        if (pPC != nullptr)
        {
            // TODO FIXME

            // // If the next coordinates differ from the current coordinates then the entity needs moving
            // if (pPC->nextCoordinates != pPC->position)
            // {
            //     // Check if the entity is allowed to occupy the next tile
            //     if (OccupyRules::canOccupy(upEntity.get(), pDistrict->getTile(pPC->nextCoordinates)))
            //     {
            //         pPC->couldNotMove = false;

            //         Tile *pTile;

            //         // Inform previous tile that it is no longer occupied by the entity
            //         pTile = pDistrict->getTile(pPC->position);
            //         if (pTile != nullptr)
            //             pTile->setEntity(nullptr);

            //         // Inform the new tile that it is now occupied by the entity
            //         pTile = pDistrict->getTile(pPC->nextCoordinates);
            //         if (pTile != nullptr)
            //             pTile->setEntity(upEntity.get());

            //         // Update position coordinates
            //         pPC->position = pPC->nextCoordinates;
            //     }
            //     else
            //     {
            //         pPC->couldNotMove = true;
            //         pPC->nextCoordinates = pPC->position; // Reset next coordinates back to the current coordinates
            //     }
            // }
        }
    }
}
