#include "Citizen.h"

#include "components/PositionComponent.h"
#include "components/WalkComponent.h"
#include "components/DrawComponent.h"
#include "components/WorkerComponent.h"
#include "components/CitizenComponent.h"
#include "helpers/CitizenNameGenerator.h"

Citizen::Citizen(TileCoordinates coords) : Citizen(CitizenNameGenerator::generateName(), coords) {}

Citizen::Citizen(const std::string& name, TileCoordinates coords) : Entity(name) {
	addComponent<PositionComponent>(coords);
	addComponent<WalkComponent>();
	addComponent<DrawComponent>('C');
	addComponent<WorkerComponent>();
	addComponent<CitizenComponent>();

	getComponent<WorkerComponent>()->working = true;
}

Citizen::~Citizen() {}
