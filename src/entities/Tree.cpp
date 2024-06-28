#include "entities/Tree.hpp"

#include "components/PositionComponent.hpp"
#include "components/RenderComponent.hpp"
#include "components/OccupySpaceComponent.hpp"
#include "components/CanBeCutDownComponent.hpp"

std::unique_ptr<Entity> makeTree(TileCoordinates coords)
{
    std::unique_ptr<Entity> tree = std::make_unique<Entity>();

    tree->addComponent(std::make_unique<PositionComponent>(coords, tree.get()));
    tree->addComponent(std::make_unique<OccupySpaceComponent>());
    tree->addComponent(std::make_unique<CanBeCutDownComponent>());
    tree->addComponent(std::make_unique<RenderComponent>('$'));

    return tree;
}
