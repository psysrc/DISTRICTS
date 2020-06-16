#include "Entity.h"

Entity::Entity(District* district, std::string objectName, char objectDrawSymbol)
: name(objectName), drawSymbol(objectDrawSymbol), pDistrict(district), pTile(nullptr) {

}

Entity::~Entity() {

}

void Entity::setTile(Tile* tile) {
	pTile = tile;
}

Tile* Entity::getTile() const {
	return pTile;
}

std::string Entity::getName() const {
	return name;
}

char Entity::getDrawSymbol() const {
	return drawSymbol;
}
