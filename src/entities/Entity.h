#ifndef SRC_ENTITY_H_
#define SRC_ENTITY_H_

#include <string>

// No need to fully include
class Tile;
class District;

class Entity {
protected:
	std::string name;		// The name of the entity
	char drawSymbol;		// The entity's visual representation in the world
	District* pDistrict;	// The district that the entity exists within
	Tile* pTile;			// The tile the entity is currently occupying
public:
	Entity();
	Entity(District*, std::string, char);
	virtual ~Entity();
	virtual void simulate() = 0;
	void setTile(Tile* tile);
	Tile* getTile() const;
	std::string getName() const;
	char getDrawSymbol() const;
};

#endif /* SRC_ENTITY_H_ */
