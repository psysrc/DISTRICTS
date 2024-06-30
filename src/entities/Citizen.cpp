#include "entities/Citizen.hpp"

#include "components/PositionComponent.hpp"
#include "components/RenderComponent.hpp"
#include "components/CitizenComponent.hpp"
#include "helpers/CitizenNameGenerator.hpp"
#include "components/NameComponent.hpp"
#include "components/TerrestrialComponent.hpp"
#include "components/OccupySpaceComponent.hpp"

std::unique_ptr<Entity> makeCitizen(TileCoordinates coords)
{
	return makeCitizen(coords, CitizenNameGenerator::generateName());
}

std::unique_ptr<Entity> makeCitizen(TileCoordinates coords, const std::string &name)
{
	std::unique_ptr<Entity> citizen = std::make_unique<Entity>();

	citizen->addComponent(std::make_unique<NameComponent>(name));
	citizen->addComponent(std::make_unique<PositionComponent>(coords, citizen.get()));
	citizen->addComponent(std::make_unique<TerrestrialComponent>());
	citizen->addComponent(std::make_unique<OccupySpaceComponent>());
	citizen->addComponent(std::make_unique<CitizenComponent>());
	citizen->addComponent(std::make_unique<RenderComponent>('C'));

	return citizen;
}
