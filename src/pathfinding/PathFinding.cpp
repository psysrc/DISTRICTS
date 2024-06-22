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
std::unique_ptr<Path> PathFinding::findPath(District *pDistrict, Entity *pEntity, DeprecatedTile *pFrom, DeprecatedTile *pTo, bool strict)
{
	// If any pointer arguments are nullptr then we can't perform any pathfinding
	if (pFrom == nullptr || pTo == nullptr || pEntity == nullptr || pDistrict == nullptr)
		return nullptr;

	// Similarly if 'from' or 'to' are not valid coordinates, no point doing pathfinding
	if (!District::validTileCoordinates(pFrom->getCoordinates()) || !District::validTileCoordinates(pTo->getCoordinates()))
		return nullptr;

	std::map<DeprecatedTile *, DeprecatedTile *> pathVia;	// The immediately-preceding tile along the currently known best path
	std::map<DeprecatedTile *, float> pathLength; // Best path length currently known
	std::map<DeprecatedTile *, float> fScore;		// pathLength + distance_heuristic

	// Open set of all tiles left to explore (with custom lambda comparator to keep the correct priority)
	auto fScoreComp = [&fScore](DeprecatedTile *a, DeprecatedTile *b) -> bool
	{ return fScore[a] < fScore[b]; };
	std::set<DeprecatedTile *, decltype(fScoreComp)> openSet(fScoreComp);

	// Closed set of all explored tiles
	std::set<DeprecatedTile *> closedSet;

	// Goal set of all tiles that the path can end with (if strict == true, this will only contain the 'to' tile)
	std::set<DeprecatedTile *> goalSet;
	goalSet.insert(pTo);

	if (!strict)
	{
		// Add each valid neighbour of the goal tile
		for (DeprecatedTile *neighbour : pDistrict->getNeighbourTiles(pTo))
		{
			goalSet.insert(neighbour);
		}
	}

	// Place the starting tile into the open set and other maps
	openSet.insert(pFrom);
	pathVia.insert(std::make_pair(pFrom, nullptr));
	pathLength.insert(std::make_pair(pFrom, 0));
	fScore.insert(std::make_pair(pFrom, 0));

	while (!openSet.empty())
	{
		// Pop the next Tile from the open set with the minimum fScore
		DeprecatedTile *pNext = *openSet.begin();
		openSet.erase(openSet.begin());

		// Check if this is a goal tile
		if (goalSet.find(pNext) != goalSet.end())
		{
			// Reconstruct the trail back to the start and return a Path object
			std::vector<DeprecatedTile *> pathFound;

			// Reserve the minimum number of tiles that may be in this path
			// This is purely for some extra efficiency when adding to the vector
			pathFound.reserve(ceil(pathLength[pNext] / 1.41) + 0.1);

			DeprecatedTile *pCurrent = pNext;

			// Populate the pathFound vector up to the starting tile ('from')
			while (pCurrent != nullptr)
			{
				pathFound.push_back(pCurrent);
				pCurrent = pathVia[pCurrent];
			}

			return std::move(std::make_unique<Path>(pathFound));
		}

		closedSet.insert(pNext);

		std::vector<DeprecatedTile *> allNeighbours = pDistrict->getNeighbourTiles(pNext);
		std::vector<DeprecatedTile *> nonDiagonalNeighbours = pDistrict->getNeighbourTiles(pNext, false);

		// For each neighbour of this tile
		for (DeprecatedTile *pNeighbour : allNeighbours)
		{
			if (closedSet.find(pNeighbour) != closedSet.end()) // If this neighbour is in the closed set, ignore it (already fully explored)
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

				pathVia[pNeighbour] = pNext;													  // New best path goes through 'next'
				pathLength[pNeighbour] = pathLengthNew;											  // New best path length
				fScore[pNeighbour] = pathLength[pNeighbour] + euclideanDistance(pNeighbour, pTo); // Update the fScore

				// Re-insert the tile to update its correct priority within the open set
				openSet.insert(pNeighbour);
			}
		}
	}

	return nullptr; // No path exists
}

float PathFinding::euclideanDistance(DeprecatedTile *pFrom, DeprecatedTile *pTo)
{
	if (pFrom == nullptr || pTo == nullptr)
		throw std::runtime_error("Cannot calculate euclidian distance with nullptr tiles");

	TileCoordinates fromCoords = pFrom->getCoordinates();
	TileCoordinates toCoords = pTo->getCoordinates();

	if (!District::validTileCoordinates(fromCoords) || !District::validTileCoordinates(toCoords))
		throw std::runtime_error("Cannot calculate euclidian distance with invalid coordinates");

	int xDiff = abs(fromCoords.x - toCoords.x);
	int yDiff = abs(fromCoords.y - toCoords.y);

	return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}
