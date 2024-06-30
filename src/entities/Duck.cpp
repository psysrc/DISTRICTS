#include "entities/Duck.hpp"

#include "components/PositionComponent.hpp"
#include "components/OccupySpaceComponent.hpp"
#include "components/RenderComponent.hpp"
#include "components/RandomWanderComponent.hpp"
#include "components/AcquaticComponent.hpp"

std::unique_ptr<Entity> makeDuck(TileCoordinates coords)
{
	std::unique_ptr<Entity> duck = std::make_unique<Entity>();

	duck->addComponent(std::make_unique<PositionComponent>(coords, duck.get()));
	duck->addComponent(std::make_unique<OccupySpaceComponent>());
	duck->addComponent(std::make_unique<AcquaticComponent>());
	duck->addComponent(std::make_unique<RandomWanderComponent>(6, 40));
	duck->addComponent(std::make_unique<RenderComponent>('d'));

	return duck;
}
