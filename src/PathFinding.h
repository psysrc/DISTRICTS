#ifndef SRC_PATHFINDING_H_
#define SRC_PATHFINDING_H_

#include "Path.h"
#include <set>				// std::set
#include <map>				// std::map
#include <cstdlib>			// abs()
#include <cmath>			// sqrt(), ceil()
#include <bits/stdc++.h>	// INT_MAX
#include "Tile.h"
#include <memory>

class PathFinding {
public:
	PathFinding() = delete;
	~PathFinding() = delete;
	static std::unique_ptr<Path> findPath(Tile*, Tile*);
	static float euclideanDistance(Tile*, Tile*);
};

#endif /* SRC_PATHFINDING_H_ */
