#include "gamesystems/GrowSystem.h"

#include "game/District.h"
#include "entities/Entity.h"
#include "components/GrowComponent.h"
#include "entities/Tree.h"

GrowSystem::GrowSystem() {}

GrowSystem::~GrowSystem() {}

void GrowSystem::run(District* pDistrict) {
    for (const std::unique_ptr<Entity>& entity : pDistrict->getEntities())
	{
		GrowComponent* gc = entity->getComponent<GrowComponent>();
		if (gc != nullptr)
		{
			gc->ticksToGrow--;

			if (gc->ticksToGrow <= 0)
			{
				entity->getTile()->vacateEntity();
				pDistrict->makeEntity<Tree>(entity->getTile());

				pDistrict->deleteEntity(entity.get());
			}
		}
	}
}