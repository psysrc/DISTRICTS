#include "gamesystems/GrowSystem.h"

#include "game/District.h"
#include "entities/Entity.h"
#include "components/GrowComponent.h"
#include "entities/Tree.h"
#include "components/PositionComponent.h"

GrowSystem::GrowSystem() {}

GrowSystem::~GrowSystem() {}

void GrowSystem::run(District* pDistrict) {
    for (const std::unique_ptr<Entity>& entity : pDistrict->getEntities())
	{
		GrowComponent* gc = entity->getComponent<GrowComponent>();
		PositionComponent* pc = entity->getComponent<PositionComponent>();
		if (gc != nullptr && pc != nullptr)
		{
			gc->ticksToGrow--;

			if (gc->ticksToGrow <= 0)
			{
				pDistrict->deleteEntity(entity.get());
				pDistrict->makeEntity<Tree>(pc->getCurrentCoordinates());
			}
		}
	}
}