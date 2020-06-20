#include "Tree.h"

#include "components/PositionComponent.h"

Tree::Tree() : Entity("Tree", '$') {
    addComponent<PositionComponent>();
}

Tree::~Tree() {}
