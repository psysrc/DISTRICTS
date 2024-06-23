#include "Tile.h"

#include "ui/TileColours.h"
#include <algorithm>

DeprecatedTile::DeprecatedTile(TileCoordinates coords) : coordinates(coords)
{

}

DeprecatedTile::~DeprecatedTile() {}

TileCoordinates DeprecatedTile::getCoordinates() const
{
	return coordinates;
}

const std::vector<Tasks::DeprecatedTask *> &DeprecatedTile::getTasks() const
{
	return tasks;
}

void DeprecatedTile::addTask(Tasks::DeprecatedTask *pTask)
{
	tasks.push_back(pTask);
}

void DeprecatedTile::removeTask(Tasks::DeprecatedTask *pTask)
{
	tasks.erase(std::find(tasks.begin(), tasks.end(), pTask));
}

bool DeprecatedTile::operator==(const DeprecatedTile &b) const
{
	return (coordinates == b.getCoordinates());
}
