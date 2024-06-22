#ifndef SRC_PATHFINDING_H_
#define SRC_PATHFINDING_H_

#include <memory>

class Path;
class DeprecatedTile;
class Entity;
class District;

class PathFinding
{
public:
	PathFinding() = delete;
	~PathFinding() = delete;
	static std::unique_ptr<Path> findPath(District *, Entity *, DeprecatedTile *, DeprecatedTile *, bool = false);
	static float euclideanDistance(DeprecatedTile *, DeprecatedTile *);
};

#endif /* SRC_PATHFINDING_H_ */
