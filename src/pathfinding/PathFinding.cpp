#include "PathFinding.hpp"

#include <unordered_map>
#include <unordered_set>
#include <set>
#include "game/TileCoordinates.hpp"
#include <cmath>
#include <bits/stdc++.h>
#include "pathfinding/Path.hpp"
#include "entities/OccupyRules.hpp"
#include "game/District.hpp"

/*
 * Finds a path between 'from' and 'to', for the given entity.
 * If no path can be found, returns nullptr.
 * 'strict' parameter defines whether the path *must* end with the goal node 'to'. By default this is disabled.
 * 		If strict is disabled, the returned solution can be a path to a neighbour of the goal instead.
 * 		This can be useful if the goal tile is a Water tile next to land, or a tile with an Entity on it, for example.
 */
std::unique_ptr<Path> PathFinding::findPath(District *pDistrict, Entity *pEntity, TileCoordinates from, TileCoordinates to, bool strict)
{
	// If any pointer arguments are nullptr then we can't perform any pathfinding
	if (pEntity == nullptr || pDistrict == nullptr)
		return nullptr;

	// Similarly if 'from' or 'to' are not valid coordinates, no point doing pathfinding
	if (!District::validTileCoordinates(from) || !District::validTileCoordinates(to))
		return nullptr;

	std::unordered_map<TileCoordinates, TileCoordinates> pathVia; // The immediately-preceding coordinates along the currently known best path
	std::unordered_map<TileCoordinates, float> pathLength;		  // Best path length currently known
	std::unordered_map<TileCoordinates, float> fScore;			  // pathLength + distance_heuristic

	// Open set of all tiles left to explore (with custom lambda comparator to keep the correct priority)
	auto fScoreComp = [&fScore](TileCoordinates a, TileCoordinates b) -> bool
	{ return fScore[a] < fScore[b]; };
	std::set<TileCoordinates, decltype(fScoreComp)> openSet(fScoreComp);

	// Closed set of all explored tiles
	std::unordered_set<TileCoordinates> closedSet;

	// Goal set of all tiles that the path can end with (if strict == true, this will only contain the 'to' tile)
	std::unordered_set<TileCoordinates> goalSet;
	goalSet.insert(to);

	if (!strict)
	{
		// Add each valid neighbour of the goal tile
		for (TileCoordinates neighbour : pDistrict->getNeighbourCoordinates(to))
		{
			goalSet.insert(neighbour);
		}
	}

	// Place the starting tile into the open set and other maps
	openSet.insert(from);
	pathLength.insert(std::make_pair(from, 0));
	fScore.insert(std::make_pair(from, 0));

	while (!openSet.empty())
	{
		// Pop the next Tile from the open set with the minimum fScore
		TileCoordinates pNext = *openSet.begin();
		openSet.erase(openSet.begin());

		// Check if this is a goal tile
		if (goalSet.contains(pNext))
		{
			// Reconstruct the trail back to the start and return a Path object
			std::vector<TileCoordinates> pathFound;

			// Reserve the minimum number of tiles that may be in this path
			// This is purely for some extra efficiency when adding to the vector
			pathFound.reserve(ceil(pathLength[pNext] / 1.41) + 0.1);

			TileCoordinates pCurrent = pNext;

			// Populate the pathFound vector up to (not including) the starting tile ('from')
			while (pCurrent != from)
			{
				pathFound.push_back(pCurrent);
				pCurrent = pathVia.at(pCurrent);
			}

			pathFound.push_back(from); // Add the starting tile

			return std::make_unique<Path>(pathFound);
		}

		closedSet.insert(pNext);

		std::vector<TileCoordinates> allNeighbours = pDistrict->getNeighbourCoordinates(pNext);
		std::vector<TileCoordinates> nonDiagonalNeighbours = pDistrict->getNeighbourCoordinates(pNext, false);

		// For each neighbour of this tile
		for (TileCoordinates pNeighbour : allNeighbours)
		{
			if (closedSet.contains(pNeighbour)) // If this neighbour is in the closed set, ignore it (already fully explored)
				continue;

			if (!OccupyRules::canOccupy(pDistrict, pEntity, pNeighbour)) // If the entity cannot occupy the tile, ignore it
				continue;

			if (openSet.find(pNeighbour) == openSet.end())
			{ // If this neighbour is not in the open set
				// Add the neighbour to the open set and all maps
				openSet.insert(pNeighbour);
				pathVia.insert(std::make_pair(pNeighbour, pNext));
				pathLength.insert(std::make_pair(pNeighbour, INT_MAX));
				fScore.insert(std::make_pair(pNeighbour, INT_MAX));
			}

			float dist;

			// If neighbour is on a diagonal, penalise its length
			if (std::find(nonDiagonalNeighbours.begin(), nonDiagonalNeighbours.end(), pNeighbour) == nonDiagonalNeighbours.end())
				dist = 1.41;
			else
				dist = 1.0;

			float pathLengthNew = pathLength[pNext] + dist; // Distance between start, next and this neighbour

			// If new length is better than the current best, update everything
			if (pathLengthNew < pathLength[pNeighbour])
			{
				openSet.erase(pNeighbour); // Remove the neighbour from the open set

				pathVia.insert(std::make_pair(pNeighbour, pNext));								 // New best path goes through 'next'
				pathLength[pNeighbour] = pathLengthNew;											 // New best path length
				fScore[pNeighbour] = pathLength[pNeighbour] + euclideanDistance(pNeighbour, to); // Update the fScore

				// Re-insert the tile to update its correct priority within the open set
				openSet.insert(pNeighbour);
			}
		}
	}

	return nullptr; // No path exists
}

float PathFinding::euclideanDistance(TileCoordinates first, TileCoordinates second)
{
	if (!District::validTileCoordinates(first) || !District::validTileCoordinates(second))
	{
		throw std::runtime_error("Cannot calculate euclidian distance with invalid coordinates");
	}

	int xDiff = abs(first.x - second.x);
	int yDiff = abs(first.y - second.y);

	return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}
