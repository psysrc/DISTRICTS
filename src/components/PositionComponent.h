#ifndef POSITIONCOMPONENT_H_
#define POSITIONCOMPONENT_H_

#include "components/Component.h"
#include "game/Tile.h"

class Tile;

class PositionComponent : public Component {
public:
    PositionComponent(short x, short y) : PositionComponent(TileCoordinates(x, y)) {}
    PositionComponent(TileCoordinates coords) : nextCoordinates(coords), currentCoordinates(-1, -1), couldNotMove(false) {}
    virtual ~PositionComponent() {}
    TileCoordinates getCurrentCoordinates() const { return currentCoordinates; }
    bool failedToMove() const { return couldNotMove; }

    TileCoordinates nextCoordinates;

private:
    friend class MoveSystem;
    
    TileCoordinates currentCoordinates;
    bool couldNotMove;
};

#endif /* POSITIONCOMPONENT_H_ */