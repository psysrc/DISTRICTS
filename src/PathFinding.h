#ifndef SRC_PATHFINDING_H_
#define SRC_PATHFINDING_H_

#include "Path.h"
#include <set>		// std::set
#include <map>		// std::map
#include <cstdlib>	// abs()
#include "Tile.h"
#include <bits/stdc++.h>	// INT_MAX
#include "UI.h"

class PathFinding {
public:
	PathFinding() = delete;
	~PathFinding() = delete;
	static Path* findPath(Tile*, Tile*);
	static int diagonalDistance(Tile*, Tile*);
};

#endif /* SRC_PATHFINDING_H_ */
