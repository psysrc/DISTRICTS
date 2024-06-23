#ifndef SRC_PATHFINDING_H_
#define SRC_PATHFINDING_H_

#include <memory>
#include "game/TileCoordinates.h"

class Path;
class Entity;
class District;

class PathFinding
{
public:
	PathFinding() = delete;
	~PathFinding() = delete;
	static std::unique_ptr<Path> findPath(District *pDistrict, Entity *pEntity, TileCoordinates from, TileCoordinates to, bool strict = false);
	static float euclideanDistance(TileCoordinates, TileCoordinates);
};

#endif /* SRC_PATHFINDING_H_ */
