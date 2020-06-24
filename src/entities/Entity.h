#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include <string>
#include <algorithm>
#include <vector>
#include <memory>
#include "components/Component.h"

class Entity {
protected:
	std::string name;		// The name of the entity
	std::vector<std::unique_ptr<Component>> components;
public:
	Entity();
	Entity(std::string);
	virtual ~Entity();
	std::string getName() const;
	template <class C> bool hasComponent() const;
	template <class C> C* getComponent() const;
	template <class C, typename... CArgs> C* addComponent(CArgs...);
};

/**
 * Returns whether or not the entity contains the given component type.
 */
template <class C>
bool Entity::hasComponent() const {
	return getComponent<C>() != nullptr;
}

/**
 * Returns a pointer to the given component if the Entity has one.
 */
template <class C>
C* Entity::getComponent() const {
	static_assert(std::is_base_of<Component, C>::value, "C must extend Component");

	// Find if a component exists within the entity which has the same type as the provided component
	auto compIt = std::find_if(components.begin(), components.end(), [](const std::unique_ptr<Component>& comp) -> bool {
		return (typeid(*comp) == typeid(C));
	});

	// Return the component if found, otherwise return nullptr
	if (compIt != components.end())
	{
		/**
		 * 1. Dereference the iterator to a unique_ptr<Component>
		 * 2. Get the raw pointer (Component*)
		 * 3. Dynamic cast to the type we already know it is (C*)
		 */
		return dynamic_cast<C*>( (*compIt).get() );
	}
	else
	{
		return nullptr;
	}
}

/**
 * Adds the given component to the entity, passing any arguments to the component's constructor.
 * Throws std::runtime_error if the entity already has the provided component.
 * Returns the newly created component.
 */
template <class C, typename... CArgs>
C* Entity::addComponent(CArgs... args) {
	static_assert(std::is_base_of<Component, C>::value, "C must extend Component");

	if (hasComponent<C>())
		throw std::runtime_error("Tried to add X component to entity which already has one");

	// Create the component, passing the method arguments to its constructor
	std::unique_ptr<C> upNewComponent = std::make_unique<C>(args...);
	C* pNewComponent = upNewComponent.get();

	components.push_back(std::move(upNewComponent));

	return pNewComponent;
}

#endif /* SRC_ENTITY_H_ */
