#include "Tile.h"

#include "ui/TileColours.h"
#include <algorithm>

Tile::Tile(TileCoordinates coords) : coordinates(coords), pEntity(nullptr)
{

}

Tile::~Tile() {}

TileCoordinates Tile::getCoordinates() const
{
	return coordinates;
}

Entity *Tile::getEntity() const
{
	return pEntity;
}

void Tile::setEntity(Entity *pEntity)
{
	this->pEntity = pEntity;
}

const std::vector<Tasks::Task *> &Tile::getTasks() const
{
	return tasks;
}

void Tile::addTask(Tasks::Task *pTask)
{
	tasks.push_back(pTask);
}

void Tile::removeTask(Tasks::Task *pTask)
{
	tasks.erase(std::find(tasks.begin(), tasks.end(), pTask));
}

bool Tile::operator==(const Tile &b) const
{
	return (coordinates == b.getCoordinates());
}
