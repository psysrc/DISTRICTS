#include "Entity.h"

Entity::Entity() : name("") {}

Entity::Entity(std::string objectName) : name(objectName) {}

Entity::~Entity() {}

std::string Entity::getName() const {
	return name;
}
