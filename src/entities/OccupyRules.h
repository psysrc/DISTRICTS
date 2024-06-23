#ifndef OCCUPYRULES_H_
#define OCCUPYRULES_H_

#include "game/TileCoordinates.h"

class Entity;
class DeprecatedTile;
class District;

class OccupyRules
{
public:
    static bool canOccupy(District * district, const Entity * tile);
    static bool canOccupy(District * district, TileCoordinates coordinates);
};

#endif /* OCCUPYRULES_H_ */
