#include "PathFinding.h"

/*
 * Finds a path between 'from' and 'to'.
 */
Path* PathFinding::findPath(Tile* from, Tile* to) {
	std::set<Tile*> openSet;
	std::set<Tile*> closedSet;

	std::map<Tile*, Tile*> pathVia;		// The immediately-preceding tile along the currently known best path
	std::map<Tile*, int> pLength;		// Best path length currently known
	std::map<Tile*, int> fScore;		// pLength + distance_heuristic

	// Place the starting Tile into the open set
	openSet.insert(from);
	pLength.insert(std::make_pair(from, 0));

	while (!openSet.empty()) {
		// Pop the next minimum PathTile from the open set
		Tile* next = *openSet.begin();
		openSet.erase(openSet.begin());



		/*
		 * for each neighbour:
		 * 		if not in closedSet
		 * 			if not in openSet
		 * 				calculate distRemaining and create PathTile
		 * 			if ("poppedLength + 1" < neighbourPathLength)
		 * 				neighbourPathLength = ""
		 * 				neighbourPathVia = popped
		 *
		 * add popped to closed set
		 */
	}

	return nullptr;
}

int PathFinding::diagonalDistance(Tile* from, Tile* to) {
	int xDiff = abs(from->getX() - to->getX());
	int yDiff = abs(from->getY() - to->getY());

	return (xDiff > yDiff) ? xDiff : yDiff;		// max(xDiff, yDiff)
}
