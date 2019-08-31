#ifndef SRC_PATHFINDING_H_
#define SRC_PATHFINDING_H_

#include "Tile.h"
#include "Path.h"
#include <queue>	// priority_queue
#include <cstdlib>	// abs()

class PathFinding {
public:
	PathFinding() = delete;
	~PathFinding() = delete;
	static Path* findPath(Tile*, Tile*);
	static int diagonalDistance(Tile*, Tile*);
};

#endif /* SRC_PATHFINDING_H_ */
