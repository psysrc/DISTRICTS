#ifndef SRC_PATHFINDING_H_
#define SRC_PATHFINDING_H_

#include <memory>

class Path;
class Tile;
class Entity;

class PathFinding {
public:
	PathFinding() = delete;
	~PathFinding() = delete;
	static std::unique_ptr<Path> findPath(Entity*, Tile*, Tile*, bool = false);
	static float euclideanDistance(Tile*, Tile*);
};

#endif /* SRC_PATHFINDING_H_ */
