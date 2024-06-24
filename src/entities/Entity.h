#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>
#include "components/Component.h"
#include "game/ID.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	ID_t getID() const;

	void addComponent(std::unique_ptr<Component>);

	template <class C>
	void removeComponent();

	template <class C>
	bool hasComponent() const;

	template <class C>
	C *getComponent() const;

private:
	const ID_t id;
	std::vector<std::unique_ptr<Component>> components;
};

template <class C>
void Entity::removeComponent()
{
	static_assert(std::is_base_of<Component, C>::value, "C must extend Component");

	// Find if a component exists within the entity which has the same type as the provided component
	auto compIt = std::find_if(components.begin(), components.end(), [](const std::unique_ptr<Component> &comp) -> bool
							   { return (typeid(*comp) == typeid(C)); });

	// Remove the component if found
	if (compIt != components.end())
	{
		components.erase(compIt);
	}
	else
	{
		throw std::runtime_error("Tried to remove a component from an entity, but the entity does not have a component of that type: "
			+ std::string(typeid(C).name()));
	}
}

/**
 * Returns whether or not the entity contains the given component type.
 */
template <class C>
bool Entity::hasComponent() const
{
	return getComponent<C>() != nullptr;
}

/**
 * Returns a pointer to the given component if the Entity has one.
 */
template <class C>
C *Entity::getComponent() const
{
	static_assert(std::is_base_of<Component, C>::value, "C must extend Component");

	// Find if a component exists within the entity which has the same type as the provided component
	auto compIt = std::find_if(components.begin(), components.end(), [](const std::unique_ptr<Component> &comp) -> bool
							   { return (typeid(*comp) == typeid(C)); });

	// Return the component if found, otherwise return nullptr
	if (compIt != components.end())
	{
		/**
		 * 1. Dereference the iterator to a unique_ptr<Component>
		 * 2. Get the raw pointer (Component*)
		 * 3. Dynamic cast to the type we already know it is (C*)
		 */
		return dynamic_cast<C *>((*compIt).get());
	}
	else
	{
		return nullptr;
	}
}

#endif /* SRC_ENTITY_H_ */
