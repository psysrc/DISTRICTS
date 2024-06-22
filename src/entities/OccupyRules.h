#ifndef OCCUPYRULES_H_
#define OCCUPYRULES_H_

class Entity;
class DeprecatedTile;
class District;

class OccupyRules
{
public:
    static bool canOccupy(District *, Entity *, DeprecatedTile *);
};

#endif /* OCCUPYRULES_H_ */
