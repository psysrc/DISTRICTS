#ifndef POSITION_LOOKUP_H_
#define POSITION_LOOKUP_H_

#include <unordered_map>
#include <unordered_set>
#include "game/TileCoordinates.hpp"
#include "entities/Entity.hpp"

using PositionLookup = std::unordered_map<TileCoordinates, std::unordered_set<Entity*>>;

#endif /* POSITION_LOOKUP_H_ */
