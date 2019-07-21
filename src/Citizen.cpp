#include "Citizen.h"

Citizen::Citizen(string name) : name(name) {

}

Citizen::Citizen() : Citizen("unnamed") {

}

Citizen::~Citizen() {

}

/*
 * Called once per game tick.
 * This prompts the citizen to do something in the world (even if it's just moving about randomly).
 */
void Citizen::takeAction() {

}

string Citizen::getName() {
	return name;
}
