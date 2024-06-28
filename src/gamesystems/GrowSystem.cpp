#include "gamesystems/GrowSystem.hpp"

#include "game/District.hpp"
#include "entities/Entity.hpp"
#include "components/GrowComponent.hpp"
#include "components/PositionComponent.hpp"

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
