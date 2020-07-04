#include "Tree.h"

#include "components/PositionComponent.h"
#include "components/DrawComponent.h"

Tree::Tree() : Tree(TileCoordinates(-1, -1)) {}

Tree::Tree(TileCoordinates coords) : Entity("Tree") {
    addComponent<PositionComponent>(coords);
    addComponent<DrawComponent>('$');
}

Tree::~Tree() {}
