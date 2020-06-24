#include "Citizen.h"

#include "components/PositionComponent.h"
#include "components/WalkComponent.h"
#include "components/DrawComponent.h"
#include "components/WorkerComponent.h"
#include "components/CitizenComponent.h"

Citizen::Citizen() : Entity("Citizen") {
	addComponent<PositionComponent>(this);
	addComponent<WalkComponent>();
	addComponent<DrawComponent>('C');
	addComponent<WorkerComponent>();
	addComponent<CitizenComponent>();

	getComponent<WorkerComponent>()->working = true;
}

Citizen::~Citizen() {}
