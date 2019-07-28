#include "Citizen.h"

Citizen::Citizen(string name) : tile(nullptr), citizenName(name) {

}

Citizen::Citizen() : Citizen("unnamed") {

}

Citizen::~Citizen() {

}

void Citizen::setTile(Tile* tile) {
	this->tile = tile;
}

Tile* Citizen::getTile() {
	return tile;
}

/*
 * Called once per game tick.
 * This prompts the citizen to do something in the world (even if it's just moving about randomly).
 */
void Citizen::takeAction() {

}

string Citizen::getName() {
	return citizenName;
}
