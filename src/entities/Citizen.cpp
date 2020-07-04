#include "Citizen.h"

#include "components/PositionComponent.h"
#include "components/WalkComponent.h"
#include "components/DrawComponent.h"
#include "components/WorkerComponent.h"
#include "components/CitizenComponent.h"

Citizen::Citizen() : Citizen(TileCoordinates(-1, -1)) {}

Citizen::Citizen(TileCoordinates coords) : Entity("Citizen") {
	addComponent<PositionComponent>(coords);
	addComponent<WalkComponent>();
	addComponent<DrawComponent>('C');
	addComponent<WorkerComponent>();
	addComponent<CitizenComponent>();

	getComponent<WorkerComponent>()->working = true;
}

Citizen::~Citizen() {}
