#include "PathFinding.h"

/*
 * Finds a path between 'from' and 'to'.
 */
std::unique_ptr<Path> PathFinding::findPath(Tile* from, Tile* to) {
	std::map<Tile*, Tile*> pathVia;		// The immediately-preceding tile along the currently known best path
	std::map<Tile*, float> pLength;		// Best path length currently known
	std::map<Tile*, float> fScore;		// pLength + distance_heuristic

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
			// Reconstruct the trail back to the start and return a Path object
			std::vector<Tile*> pathFound;

			// Reserve (pathLength/1.41) objects (the minimum number of tiles that may be in this path)
			pathFound.reserve(ceil(pLength[next] / 1.41) + 0.1);

			Tile* current = to;

			// Populate the pathFound vector up to the first tile from the start
			while (current != from) {
				pathFound.push_back(current);
				current = pathVia[current];
			}

			return std::move(std::make_unique<Path>(pathFound));
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

			float dist;

			// If neighbour is on a diagonal, penalise its length
			if (n == 0 || n == 2 || n == 5 || n == 7)
				dist = 1.41;
			else
				dist = 1.0;

			float pLengthNew = pLength[next] + dist;		// Distance between start, next and this neighbour

			// If new length is better than the current best, update everything
			if (pLengthNew < pLength[neighbour]) {
				openSet.erase(neighbour);	// Remove the neighbour from the open set

				pathVia[neighbour] = next;			// New best path goes through 'next'
				pLength[neighbour] = pLengthNew;	// New best path length
				fScore[neighbour] = pLength[neighbour] + euclideanDistance(neighbour, to);	// Update the fScore

				// Re-insert the tile to update its correct priority within the open set
				openSet.insert(neighbour);
			}
		}
	}

	return nullptr;		// No path exists
}

float PathFinding::euclideanDistance(Tile* from, Tile* to) {
	int xDiff = abs(from->getX() - to->getX());
	int yDiff = abs(from->getY() - to->getY());

	return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}
