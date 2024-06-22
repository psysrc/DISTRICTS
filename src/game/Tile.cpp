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
