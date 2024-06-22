#ifndef OCCUPYRULES_H_
#define OCCUPYRULES_H_

class Entity;
class Tile;
class District;

class OccupyRules
{
public:
    static bool canOccupy(District *, Entity *, Tile *);
};

#endif /* OCCUPYRULES_H_ */
