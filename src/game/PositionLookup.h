#ifndef POSITION_LOOKUP_H_
#define POSITION_LOOKUP_H_

#include <unordered_map>
#include <unordered_set>
#include "game/TileCoordinates.h"
#include "entities/Entity.h"

using PositionLookup = std::unordered_map<TileCoordinates, std::unordered_set<Entity*>>;

#endif /* POSITION_LOOKUP_H_ */
