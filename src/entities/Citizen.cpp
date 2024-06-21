#include "entities/Citizen.h"

#include "components/PositionComponent.h"
#include "components/WalkComponent.h"
#include "components/RenderComponent.h"
#include "components/WorkerComponent.h"
#include "components/CitizenComponent.h"
#include "helpers/CitizenNameGenerator.h"
#include "components/NameComponent.h"

std::unique_ptr<Entity> makeCitizen(TileCoordinates coords)
{
	return makeCitizen(coords, CitizenNameGenerator::generateName());
}

std::unique_ptr<Entity> makeCitizen(TileCoordinates coords, const std::string &name)
{
	std::unique_ptr<Entity> entity = std::make_unique<Entity>();

	entity->addComponent(std::make_unique<NameComponent>(name));
	entity->addComponent(std::make_unique<PositionComponent>(coords));
	entity->addComponent(std::make_unique<WalkComponent>());
	entity->addComponent(std::make_unique<WorkerComponent>());
	entity->addComponent(std::make_unique<CitizenComponent>());
	entity->addComponent(std::make_unique<RenderComponent>('C'));

	entity->getComponent<WorkerComponent>()->working = true;

	return entity;
}
