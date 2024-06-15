#include "gamesystems/GrowSystem.h"

#include "game/District.h"
#include "entities/Entity.h"
#include "components/GrowComponent.h"
#include "components/PositionComponent.h"

GrowSystem::GrowSystem() {}

GrowSystem::~GrowSystem() {}

void GrowSystem::run(District *pDistrict)
{
	for (const std::unique_ptr<Entity> &upEntity : pDistrict->getEntities())
	{
		GrowComponent *pGC = upEntity->getComponent<GrowComponent>();
		PositionComponent *pPC = upEntity->getComponent<PositionComponent>();
		if (pGC != nullptr && pPC != nullptr)
		{
			pGC->ticksToGrow--;

			if (pGC->ticksToGrow <= 0)
			{
				auto newEntity = pGC->makeNextEntity(*upEntity.get());

				pDistrict->deleteEntity(upEntity.get());

				pDistrict->addEntity(std::move(newEntity));
			}
		}
	}
}
