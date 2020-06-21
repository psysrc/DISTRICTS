#ifndef POSITIONCOMPONENT_H_
#define POSITIONCOMPONENT_H_

#include "components/Component.h"
#include "entities/Entity.h"    // Deprecated

class Tile;

class PositionComponent : public Component {
public:
    PositionComponent(Entity* /*Deprecated*/);
    virtual ~PositionComponent();

    Tile* getTile() const;
    int getX() const;
    int getY() const;

    void setTile(Tile* pTile);
    
private:
    Entity* entity; // Deprecated
    Tile* tile;
    int x;
    int y;
};

#endif /* POSITIONCOMPONENT_H_ */