#include "entities/Sapling.hpp"

#include "components/GrowComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/OccupySpaceComponent.hpp"
#include "components/RenderComponent.hpp"
#include "components/TerrestrialComponent.hpp"
#include "entities/Tree.hpp"
#include "game/TickSpeed.hpp"


constexpr int maxTicksToGrow = 60 * ticksPerSecond;
constexpr int minTicksToGrow = 5 * ticksPerSecond;

std::unique_ptr<Entity> makeSapling(TileCoordinates coords)
{
    std::unique_ptr<Entity> sapling = std::make_unique<Entity>();

    const int ticksToGrow = minTicksToGrow + (rand() % (maxTicksToGrow - minTicksToGrow + 1));

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
	sapling->addComponent(std::make_unique<OccupySpaceComponent>());
	sapling->addComponent(std::make_unique<TerrestrialComponent>());
    sapling->addComponent(std::make_unique<GrowComponent>(makeTreeFunc, ticksToGrow));
    sapling->addComponent(std::make_unique<RenderComponent>(','));

    return sapling;
}
