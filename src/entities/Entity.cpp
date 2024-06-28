#include "Entity.hpp"

Entity::Entity() : id(uniqueEntityID()) {}

Entity::~Entity() {}

ID_t Entity::getID() const
{
	return id;
}

void Entity::addComponent(std::unique_ptr<Component> component)
{
	components.push_back(std::move(component));
}
