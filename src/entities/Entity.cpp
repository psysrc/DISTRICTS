#include "Entity.h"

Entity::Entity(std::string objectName, char objectDrawSymbol)
: name(objectName), drawSymbol(objectDrawSymbol) {

}

Entity::~Entity() {

}

std::string Entity::getName() const {
	return name;
}

char Entity::getDrawSymbol() const {
	return drawSymbol;
}
