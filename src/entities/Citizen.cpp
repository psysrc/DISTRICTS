#include "entities/Citizen.h"

#include "components/PositionComponent.h"
#include "components/WalkComponent.h"
#include "components/DrawComponent.h"
#include "components/WorkerComponent.h"
#include "components/CitizenComponent.h"
#include "helpers/CitizenNameGenerator.h"

std::unique_ptr<Entity> makeCitizen(TileCoordinates coords) {
	return makeCitizen(coords, CitizenNameGenerator::generateName());
}

std::unique_ptr<Entity> makeCitizen(TileCoordinates coords, const std::string& name) {
    std::unique_ptr<Entity> entity = std::make_unique<Entity>(name);

	entity->addComponent<PositionComponent>(coords);
	entity->addComponent<WalkComponent>();
	entity->addComponent<DrawComponent>('C');
	entity->addComponent<WorkerComponent>();
	entity->addComponent<CitizenComponent>();

	entity->getComponent<WorkerComponent>()->working = true;

	return entity;
}
