#ifndef WALKCOMPONENT_H_
#define WALKCOMPONENT_H_

#include "components/Component.h"
#include "game/Tile.h"
#include "pathfinding/Path.h"

class WalkComponent : public Component {
public:
    WalkComponent() {}
    virtual ~WalkComponent() {}

    Tile* destination;
    std::unique_ptr<Path> path;
};

#endif /* WALKCOMPONENT_H_ */