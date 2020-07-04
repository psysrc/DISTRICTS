#include "PathFinding.h"

#include <map>
#include <set>
#include "game/Tile.h"
#include <cmath>
#include <bits/stdc++.h>
#include "pathfinding/Path.h"
#include "entities/OccupyRules.h"
#include "game/District.h"

/*
 * Finds a path between 'from' and 'to', for the given entity.
 * If no path can be found, returns nullptr.
 * 'strict' parameter defines whether the path *must* end with the goal node 'to'. By default this is disabled.
 * 		If strict is disabled, the returned solution can be a path to a neighbour of the goal instead.
 * 		This can be useful if the goal tile is a Water tile next to land, or a tile with an Entity on it, for example.
 */
std::unique_ptr<Path> PathFinding::findPath(District* pDistrict, Entity* entity, Tile* from, Tile* to, bool strict) {
	if (from == nullptr || to == nullptr || entity == nullptr || pDistrict == nullptr)
		return nullptr;

	std::map<Tile*, Tile*> pathVia;		// The immediately-preceding tile along the currently known best path
	std::map<Tile*, float> pLength;		// Best path length currently known
	std::map<Tile*, float> fScore;		// pLength + distance_heuristic

	// Open set of all tiles left to explore (with custom lambda comparator to keep the correct priority)
	auto fScoreComp = [&fScore] (Tile* a, Tile* b) -> bool { return fScore[a] < fScore[b]; };
	std::set<Tile*, decltype(fScoreComp)> openSet(fScoreComp);

	// Closed set of all explored tiles
	std::set<Tile*> closedSet;

	// Goal set of all tiles that the path can end with (if strict == true, this will only contain the 'to' tile)
	std::set<Tile*> goalSet;
	goalSet.insert(to);

	if (!strict) {
		// Add each valid neighbour of the goal tile
		for (Tile* neighbour : pDistrict->getNeighbourTiles(to)) {
			goalSet.insert(neighbour);
		}
	}

	// Place the starting tile into the open set and other maps
	openSet.insert(from);
	pathVia.insert(std::make_pair(from, nullptr));
	pLength.insert(std::make_pair(from, 0));
	fScore.insert(std::make_pair(from, 0));

	while (!openSet.empty()) {
		// Pop the next Tile from the open set with the minimum fScore
		Tile* next = *openSet.begin();
		openSet.erase(openSet.begin());

		if (goalSet.find(next) != goalSet.end()) {	// If this is a goal tile
			// Reconstruct the trail back to the start and return a Path object
			std::vector<Tile*> pathFound;

			// Reserve ceiling(pathLength/1.41) objects (the minimum number of tiles that may be in this path)
			// This is purely for some extra efficiency when adding to the vector
			pathFound.reserve(ceil(pLength[next] / 1.41) + 0.1);

			Tile* current = next;

			// Populate the pathFound vector up to the starting tile ('from')
			while (current != nullptr) {
				pathFound.push_back(current);
				current = pathVia[current];
			}

			return std::move(std::make_unique<Path>(pathFound));
		}

		closedSet.insert(next);

		std::vector<Tile*> allNeighbours = pDistrict->getNeighbourTiles(next);
		std::vector<Tile*> nonDiagonalNeighbours = pDistrict->getNeighbourTiles(next, false);

		// For each neighbour of this tile
		for (Tile* neighbour : allNeighbours) {
			if (closedSet.find(neighbour) != closedSet.end())	// If this neighbour is in the closed set, ignore it (already fully explored)
				continue;

			if (!OccupyRules::canOccupy(entity, neighbour))		// If the entity cannot occupy the tile, ignore it
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
			if (std::find(nonDiagonalNeighbours.begin(), nonDiagonalNeighbours.end(), neighbour) == nonDiagonalNeighbours.end())
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
	int xDiff = abs(from->getCoordinates().x - to->getCoordinates().x);
	int yDiff = abs(from->getCoordinates().y - to->getCoordinates().y);

	return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}
