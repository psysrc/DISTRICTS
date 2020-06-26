#include "Entity.h"

// Returns a new unique EntityID_t
EntityID_t Entity::uniqueEntityID() {
	static EntityID_t nextID = 0;
	return nextID++;
}

Entity::Entity() : id(uniqueEntityID()), name("") {}

Entity::Entity(std::string objectName) : id(uniqueEntityID()), name(objectName) {}

Entity::~Entity() {}

std::string Entity::getName() const {
	return name;
}

EntityID_t Entity::getID() const {
	return id;
}