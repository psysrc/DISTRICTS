#include "entities/Chicken.h"

#include "components/PositionComponent.h"
// #include "components/WalkComponent.h"
#include "components/RenderComponent.h"
#include "components/OccupySpaceComponent.h"

std::unique_ptr<Entity> makeChicken(TileCoordinates coords)
{
	std::unique_ptr<Entity> chicken = std::make_unique<Entity>();

	chicken->addComponent(std::make_unique<PositionComponent>(coords, chicken.get()));
	chicken->addComponent(std::make_unique<OccupySpaceComponent>());
	// chicken->addComponent(std::make_unique<WalkComponent>());
	chicken->addComponent(std::make_unique<RenderComponent>('5'));

	return chicken;
}
