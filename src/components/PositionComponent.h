#ifndef POSITIONCOMPONENT_H_
#define POSITIONCOMPONENT_H_

#include "components/Component.h"
#include "game/Tile.h"

class PositionComponent : public Component {
public:
    PositionComponent() {}
    virtual ~PositionComponent() {}

    Tile* getTile() const;
    int getX() const;
    int getY() const;

    void setTile(Tile* pTile);
    
private:
    Tile* tile;
    int x;
    int y;
};

#endif /* POSITIONCOMPONENT_H_ */