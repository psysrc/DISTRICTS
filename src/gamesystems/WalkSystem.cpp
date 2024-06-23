#include "gamesystems/WalkSystem.h"

#include "game/District.h"
#include "components/WalkComponent.h"
#include "components/PositionComponent.h"
#include "pathfinding/PathFinding.h"

WalkSystem::WalkSystem() {}

WalkSystem::~WalkSystem() {}

void WalkSystem::run(District *)
{
    // for (const std::unique_ptr<Entity> &upEntity : pDistrict->getEntities())
    // {
    //     WalkComponent *pWC = upEntity->getComponent<WalkComponent>();
    //     PositionComponent *pPC = upEntity->getComponent<PositionComponent>();

    //     if (pWC != nullptr && pPC != nullptr)
    //     {
    //         /**
    //          * 1. If entity has a destination but no path, generate a path
    //          * 2. If entity has a path, check that the entity is on the path as we expect
    //          *      2a. If not, discard the path and do no more with this entity
    //          * 3. Move the entity along the path
    //          * 4. If the entity has reached the end of its path, clear the destination and path
    //          */

    //         // If entity has a destination but no path, generate a path
    //         if (pWC->pDestination && !pWC->upPath)
    //         {
    //             // Create a path from the entity's current position to the destination
    //             // If no path can be found, path will remain as nullptr
    //             pWC->upPath = PathFinding::findPath(pDistrict, upEntity.get(), pDistrict->getTile(pPC->getPosition()), pWC->pDestination);
    //         }

    //         // If entity has a path
    //         if (pWC->upPath)
    //         {
    //             // Check that the entity is where we expect along the path
    //             if (pDistrict->getTile(pPC->getPosition()) == pWC->upPath->current())
    //             {
    //                 // Get the next tile in the path
    //                 DeprecatedTile *pNextTile = pWC->upPath->next();

    //                 if (pNextTile != nullptr)
    //                 {
    //                     // Move the entity to the next tile if we haven't reached the end
    //                     // pPC->nextCoordinates = pNextTile->getCoordinates();
    //                     // TODO FIXME
    //                 }
    //                 else
    //                 {
    //                     // If nextTile is nullptr then we must be at the end of the path - clear the entity's path and destination
    //                     pWC->pDestination = nullptr;
    //                     pWC->upPath.reset();
    //                 }
    //             }
    //             else
    //             {
    //                 // The entity is not where we expected it to be along the path
    //                 // Discard the path - if the entity still has a destination then a new path will be generated next game tick
    //                 pWC->upPath.reset();
    //             }
    //         }
    //     }
    // }
}
