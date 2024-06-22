#include "Tile.h"

#include "ui/TileColours.h"
#include <algorithm>

DeprecatedTile::DeprecatedTile(TileCoordinates coords) : coordinates(coords), pEntity(nullptr)
{

}

DeprecatedTile::~DeprecatedTile() {}

TileCoordinates DeprecatedTile::getCoordinates() const
{
	return coordinates;
}

Entity *DeprecatedTile::getEntity() const
{
	return pEntity;
}

void DeprecatedTile::setEntity(Entity *pEntity)
{
	this->pEntity = pEntity;
}

const std::vector<Tasks::Task *> &DeprecatedTile::getTasks() const
{
	return tasks;
}

void DeprecatedTile::addTask(Tasks::Task *pTask)
{
	tasks.push_back(pTask);
}

void DeprecatedTile::removeTask(Tasks::Task *pTask)
{
	tasks.erase(std::find(tasks.begin(), tasks.end(), pTask));
}

bool DeprecatedTile::operator==(const DeprecatedTile &b) const
{
	return (coordinates == b.getCoordinates());
}
