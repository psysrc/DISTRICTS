#include "gamesystems/MoveSystem.h"

#include "game/District.h"
#include "components/PositionComponent.h"
#include "entities/OccupyRules.h"

MoveSystem::MoveSystem() {}

MoveSystem::~MoveSystem() {}

void MoveSystem::run(District* pDistrict) {
    for (const std::unique_ptr<Entity>& entity : pDistrict->getEntities())
	{
		PositionComponent* pc = entity->getComponent<PositionComponent>();
        if (pc != nullptr)
        {
            // If the next coordinates differ from the current coordinates then the entity needs moving
            if (pc->nextCoordinates != pc->currentCoordinates)
            {
                // Check if the entity is allowed to occupy the next tile
                if (OccupyRules::canOccupy(entity.get(), pDistrict->getTile(pc->nextCoordinates)))
                {
                    pc->couldNotMove = false;

                    Tile* tile;

                    // Inform previous tile that it is no longer occupied by the entity
                    tile = pDistrict->getTile(pc->currentCoordinates);
                    if (tile != nullptr)
                        tile->setEntity(nullptr);

                    // Inform the new tile that it is now occupied by the entity
                    tile = pDistrict->getTile(pc->nextCoordinates);
                    if (tile != nullptr)
                        tile->setEntity(entity.get());

                    // Update position coordinates
                    pc->currentCoordinates = pc->nextCoordinates;
                }
                else
                {
                    pc->couldNotMove = true;
                    pc->nextCoordinates = pc->currentCoordinates;   // Reset next coordinates back to the current coordinates
                }
            }
        }
    }
}