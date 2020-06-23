#include "gamesystems/WalkSystem.h"

#include "game/District.h"
#include "game/Tile.h"
#include "components/WalkComponent.h"
#include "components/PositionComponent.h"
#include "pathfinding/PathFinding.h"

WalkSystem::WalkSystem() {}

WalkSystem::~WalkSystem() {}

void WalkSystem::run(District* pDistrict) {
    for (const std::unique_ptr<Entity>& entity : pDistrict->getEntities())
    {
        WalkComponent* wc = entity->getComponent<WalkComponent>();
        PositionComponent* pc = entity->getComponent<PositionComponent>();

		if (wc != nullptr && pc != nullptr)
        {
            /**
             * 1. If entity has a destination but no path, generate a path
             * 2. If entity has a path, check that the entity is on the path as we expect
             *      2a. If not, discard the path and do no more with this entity
             * 3. Move the entity along the path
             * 4. If the entity has reached the end of its path, clear the destination and path
             */

            // If entity has a destination but no path, generate a path
            if (wc->destination && !wc->path)
            {
                // Create a path from the entity's current position to the destination
                // If no path can be found, path will remain as nullptr
                wc->path = PathFinding::findPath(pc->getTile(), wc->destination);
            }

            // If entity has a path
            if (wc->path)
            {
                // Check that the entity is where we expect along the path
                if (pc->getTile() == wc->path->current())
                {
                    // Move the entity to the next tile in the path, assuming we're not already at the end for some reason
                    Tile* nextTile = wc->path->next();

                    if (nextTile != nullptr)
                    {
                        pc->setTile(nextTile);
                    }

                    // Clear destination and path if the entity has now reached the end of the path (or if it was at the end already)
                    if (pc->getTile() == wc->path->end() || nextTile == nullptr)
                    {
                        wc->destination = nullptr;
                        wc->path.reset();
                    }
                }
                else
                {
                    // The entity is not where we expected it to be along the path
                    // Discard the path - if the entity still has a destination then a new path will be generated next game tick
                    wc->path.reset();
                }
            }
        }
    }
}