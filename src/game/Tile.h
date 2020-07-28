#ifndef TILE_H_
#define TILE_H_

#include "game/TileCoordinates.h"
#include "game/TileProperty.h"
#include <vector>
#include "tasks/Task.h"

class District;
class Entity;

class Tile {
private:
	TileCoordinates coordinates;
	Entity* pEntity;
	TileProperty::TileProperty property;
	int drawColour;
	std::vector<Tasks::Task*> tasks;
public:
	Tile(TileCoordinates, TileProperty::TileProperty);
	~Tile();
	TileCoordinates getCoordinates() const;
	void updateProperty(TileProperty::TileProperty newProperty);
	TileProperty::TileProperty getProperty() const;
	Entity* getEntity() const;
	void setEntity(Entity*);
	const std::vector<Tasks::Task*>& getTasks() const;
	void addTask(Tasks::Task*);
	void removeTask(Tasks::Task*);
	int getDrawColour() const;
	void updateColour();
	bool operator==(const Tile& b) const;
};

#endif /* TILE_H_ */
