#include "gamesystems/GrowSystem.hpp"

#include "game/District.hpp"
#include "entities/Entity.hpp"
#include "components/GrowComponent.hpp"
#include "components/PositionComponent.hpp"

GrowSystem::GrowSystem() {}

GrowSystem::~GrowSystem() {}

void GrowSystem::processEntity(District *district, const std::unique_ptr<Entity> &entity)
{
	GrowComponent *growComponent = entity->getComponent<GrowComponent>();
	if (growComponent)
	{
		growComponent->ticksToGrow--;

		if (growComponent->ticksToGrow <= 0)
		{
			auto newEntity = growComponent->makeNextEntity(*entity.get());

			district->deleteEntity(entity.get());

			district->addEntity(std::move(newEntity));
		}
	}
}
