#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include <string>

class Entity {
protected:
	std::string name;		// The name of the entity
	char drawSymbol;		// The entity's visual representation in the world
public:
	Entity();
	Entity(std::string, char);
	virtual ~Entity();
	virtual void simulate() = 0;
	std::string getName() const;
	char getDrawSymbol() const;
};

#endif /* SRC_ENTITY_H_ */
