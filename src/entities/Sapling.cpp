#include "entities/Sapling.h"

#include "components/GrowComponent.h"
#include "components/PositionComponent.h"
#include "components/RenderComponent.h"
#include "entities/Tree.h"


constexpr int maxSecondsToGrow = 6 * 60;
constexpr int minSecondsToGrow = 2 * 60;

std::unique_ptr<Entity> makeSapling(TileCoordinates coords)
{
    std::unique_ptr<Entity> sapling = std::make_unique<Entity>();

    int secondsToGrow = minSecondsToGrow + (rand() % (maxSecondsToGrow - minSecondsToGrow + 1));

    GrowComponent::MakeNextEntityMethod_t makeTreeFunc = [](const Entity& self)
    {
        const auto& pos = self.getComponent<PositionComponent>();

        if (!pos)
        {
            throw std::runtime_error("Tried to turn a sapling into a tree, but the sapling doesn't have a PositionComponent");
        }

        return makeTree(pos->getPosition());
    };

    sapling->addComponent(std::make_unique<PositionComponent>(coords, sapling.get()));
    sapling->addComponent(std::make_unique<GrowComponent>(makeTreeFunc, secondsToGrow));
    sapling->addComponent(std::make_unique<RenderComponent>(','));

    return sapling;
}
