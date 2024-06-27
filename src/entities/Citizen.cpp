#include "entities/Citizen.h"

#include "components/PositionComponent.h"
#include "components/RenderComponent.h"
#include "components/CitizenComponent.h"
#include "helpers/CitizenNameGenerator.h"
#include "components/NameComponent.h"
#include "components/OccupySpaceComponent.h"

std::unique_ptr<Entity> makeCitizen(TileCoordinates coords)
{
	return makeCitizen(coords, CitizenNameGenerator::generateName());
}

std::unique_ptr<Entity> makeCitizen(TileCoordinates coords, const std::string &name)
{
	std::unique_ptr<Entity> citizen = std::make_unique<Entity>();

	citizen->addComponent(std::make_unique<NameComponent>(name));
	citizen->addComponent(std::make_unique<PositionComponent>(coords, citizen.get()));
	citizen->addComponent(std::make_unique<OccupySpaceComponent>());
	citizen->addComponent(std::make_unique<CitizenComponent>());
	citizen->addComponent(std::make_unique<RenderComponent>('C'));

	return citizen;
}
