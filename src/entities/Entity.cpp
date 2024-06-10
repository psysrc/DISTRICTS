#include "Entity.h"

Entity::Entity() : id(uniqueEntityID()), name("") {}

Entity::Entity(std::string objectName) : id(uniqueEntityID()), name(objectName) {}

Entity::~Entity() {}

std::string Entity::getName() const
{
	return name;
}

ID_t Entity::getID() const
{
	return id;
}
