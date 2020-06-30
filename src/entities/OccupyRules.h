#ifndef OCCUPYRULES_H_
#define OCCUPYRULES_H_

class Entity;
class Tile;

class OccupyRules {
public:
    static bool canOccupy(Entity*, Tile*);
};

#endif /* OCCUPYRULES_H_ */