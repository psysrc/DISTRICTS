#include "PathFinding.h"

/*
 * Finds a path between 'from' and 'to'.
 */
Path* PathFinding::findPath(Tile* from, Tile* to) {
	std::map<Tile*, Tile*> pathVia;		// The immediately-preceding tile along the currently known best path
	std::map<Tile*, int> pLength;		// Best path length currently known
	std::map<Tile*, int> fScore;		// pLength + distance_heuristic

	// OpenSet of all tiles left to explore (with custom lambda comparator to keep correct priority)
	auto fScoreComp = [&fScore] (Tile* a, Tile* b) -> bool { return fScore[a] < fScore[b]; };
	std::set<Tile*, decltype(fScoreComp)> openSet(fScoreComp);

	// Closed set of all explored tiles
	std::set<Tile*> closedSet;

	// Place the starting tile into the open set and other maps
	openSet.insert(from);
	pathVia.insert(std::make_pair(from, nullptr));
	pLength.insert(std::make_pair(from, 0));
	fScore.insert(std::make_pair(from, 0));

	while (!openSet.empty()) {
		// Pop the next Tile from the open set with the minimum fScore
		Tile* next = *openSet.begin();
		openSet.erase(openSet.begin());

		if (next == to) {	// If this is the goal
			// TODO: Reconstruct the trail back to the start and return a Path object
			// pLength (+1?) is the number of tiles in the path

			Tile* current = next;

			// Go through the path and set to NullProperty to visualise the path
			while (current != nullptr) {
				current->updateProperty(NullProperty);
				current = pathVia[current];
			}

			return new Path(std::vector<Tile*>());		// Temporary - will eventually return a Path object
		}

		closedSet.insert(next);

		// For each neighbour of this tile
		for (int n = 0; n < 8; n++) {
			Tile* neighbour = next->getNeighbourTile(n);

			if (neighbour == nullptr)	// If this neighbour is non-existent, ignore it
				continue;

			if (closedSet.find(neighbour) != closedSet.end())	// If this neighbour is in the closed set, ignore it (already fully explored)
				continue;

			if (!neighbour->walkable())		// If the tile is not walkable, ignore it
				continue;

			if (openSet.find(neighbour) == openSet.end()) {		// If this neighbour is not in the open set
				// Add the neighbour to the open set and all maps
				openSet.insert(neighbour);
				pathVia.insert(std::make_pair(neighbour, next));
				pLength.insert(std::make_pair(neighbour, INT_MAX));
				fScore.insert(std::make_pair(neighbour, INT_MAX));
			}

			int pLengthNew = pLength[next] + 1;		// Distance between start, next and this neighbour

			// If new length is better than the current best, update everything
			if (pLengthNew < pLength[neighbour]) {
				pathVia[neighbour] = next;			// New best path goes through 'next'
				pLength[neighbour] = pLengthNew;	// New best path length
				fScore[neighbour] = pLength[neighbour] + diagonalDistance(neighbour, to);	// Update the fScore

				// Re-insert the tile to update its correct priority within the set
				openSet.erase(neighbour);
				openSet.insert(neighbour);
			}
		}
	}

	return nullptr;		// No path exists
}

int PathFinding::diagonalDistance(Tile* from, Tile* to) {
	int xDiff = abs(from->getX() - to->getX());
	int yDiff = abs(from->getY() - to->getY());

	return (xDiff > yDiff) ? xDiff : yDiff;		// max(xDiff, yDiff)
}
