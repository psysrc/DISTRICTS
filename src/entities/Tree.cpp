#include "Tree.h"

#include "components/PositionComponent.h"
#include "components/DrawComponent.h"

Tree::Tree() : Entity("Tree", '$') {
    addComponent<PositionComponent>();
    addComponent<DrawComponent>('$');
}

Tree::~Tree() {}
