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
		if (gc != nullptr)
		{
			gc->ticksToGrow--;

			if (gc->ticksToGrow <= 0)
			{
				PositionComponent* pc = entity->getComponent<PositionComponent>();
				if (pc && pc->getTile())
					pc->getTile()->vacateEntity();

				Tree* newTree = pDistrict->makeEntity<Tree>();
				newTree->getComponent<PositionComponent>()->setTile(pc->getTile());

				pDistrict->deleteEntity(entity.get());
			}
		}
	}
}