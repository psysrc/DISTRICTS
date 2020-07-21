#include "gamesystems/GrowSystem.h"

#include "game/District.h"
#include "entities/Entity.h"
#include "components/GrowComponent.h"
#include "entities/Tree.h"
#include "components/PositionComponent.h"

GrowSystem::GrowSystem() {}

GrowSystem::~GrowSystem() {}

void GrowSystem::run(District* pDistrict) {
    for (const std::unique_ptr<Entity>& upEntity : pDistrict->getEntities())
	{
		GrowComponent* pGC = upEntity->getComponent<GrowComponent>();
		PositionComponent* pPC = upEntity->getComponent<PositionComponent>();
		if (pGC != nullptr && pPC != nullptr)
		{
			pGC->ticksToGrow--;

			if (pGC->ticksToGrow <= 0)
			{
				pDistrict->deleteEntity(upEntity.get());
				pDistrict->makeEntity<Tree>(pPC->getCurrentCoordinates());
			}
		}
	}
}