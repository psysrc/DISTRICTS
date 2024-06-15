#ifndef WALKCOMPONENT_H_
#define WALKCOMPONENT_H_

#include "components/Component.h"
#include "game/Tile.h"
#include "pathfinding/Path.h"

struct WalkComponent : public Component
{
    WalkComponent() {}

    virtual ~WalkComponent() = default;

    Tile *pDestination = nullptr;
    std::unique_ptr<Path> upPath = nullptr;
};

#endif /* WALKCOMPONENT_H_ */
