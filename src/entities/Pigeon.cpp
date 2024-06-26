#include "entities/Pigeon.h"

#include "components/PositionComponent.h"
#include "components/OccupySpaceComponent.h"
#include "components/RenderComponent.h"
#include "components/RandomWanderComponent.h"

std::unique_ptr<Entity> makePigeon(TileCoordinates coords)
{
	std::unique_ptr<Entity> pigeon = std::make_unique<Entity>();

	pigeon->addComponent(std::make_unique<PositionComponent>(coords, pigeon.get()));
	pigeon->addComponent(std::make_unique<OccupySpaceComponent>());
	pigeon->addComponent(std::make_unique<RandomWanderComponent>(4, 40));
	pigeon->addComponent(std::make_unique<RenderComponent>('p'));

	return pigeon;
}
