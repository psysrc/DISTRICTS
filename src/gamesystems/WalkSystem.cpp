#include "gamesystems/WalkSystem.h"

#include "game/District.h"
#include "components/WalkComponent.h"

WalkSystem::WalkSystem() {}

WalkSystem::~WalkSystem() {}

void WalkSystem::run(District* pDistrict) {
    for (const std::unique_ptr<Entity>& entity : pDistrict->getEntities())
    {
        WalkComponent* wc = entity->getComponent<WalkComponent>();
		if (wc != nullptr)
        {
            /**
             * 1. If entity destination is nullptr, do nothing
             * 2. If entity is at its destination, clear destination and path, then do nothing
             * 3. If entity path is nullptr, use pathfinding to generate a path
             *      3a. Move the entity along the path
             * 4. Check the entity resides on its expected tile within the current path
             *      4a. If it does not, discard the path and generate a new one
             * 5. Move the entity along the path
             */

            // !! Need to deal with strictness - the entity might be next to its destination, not directly on it

            // Skip this entity if it has no destination
            if (wc->destination == nullptr)
                continue;
            

        }
    }
}