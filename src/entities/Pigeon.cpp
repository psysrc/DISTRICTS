#include "entities/Pigeon.h"

#include "components/PositionComponent.h"
// #include "components/WalkComponent.h"
#include "components/RenderComponent.h"
#include "components/OccupySpaceComponent.h"

std::unique_ptr<Entity> makePigeon(TileCoordinates coords)
{
	std::unique_ptr<Entity> pigeon = std::make_unique<Entity>();

	pigeon->addComponent(std::make_unique<PositionComponent>(coords, pigeon.get()));
	pigeon->addComponent(std::make_unique<OccupySpaceComponent>());
	// pigeon->addComponent(std::make_unique<WalkComponent>());
	pigeon->addComponent(std::make_unique<RenderComponent>('5'));

	return pigeon;
}
