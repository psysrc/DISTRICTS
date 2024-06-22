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
		GrowComponent *growComponent = upEntity->getComponent<GrowComponent>();
		if (growComponent)
		{
			growComponent->ticksToGrow--;

			if (growComponent->ticksToGrow <= 0)
			{
				auto newEntity = growComponent->makeNextEntity(*upEntity.get());

				pDistrict->deleteEntity(upEntity.get());

				pDistrict->addEntity(std::move(newEntity));
			}
		}
	}
}
