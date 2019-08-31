#include "PathFinding.h"

/*
 * Finds a path between 'from' and 'to'.
 */
Path* PathFinding::findPath(Tile* from, Tile* to) {
	std::priority_queue<Tile*> openQueue;
	std::vector<Tile*> closedQueue;


}

int PathFinding::diagonalDistance(Tile* from, Tile* to) {
	int xDiff = abs(from->getX() - to->getX());
	int yDiff = abs(from->getY() - to->getY());

	return (xDiff > yDiff) ? xDiff : yDiff;		// max(xDiff, yDiff)
}
