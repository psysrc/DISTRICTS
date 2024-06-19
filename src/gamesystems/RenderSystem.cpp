#include "gamesystems/RenderSystem.h"

#include "game/District.h"
#include "components/PositionComponent.h"
#include "components/TileComponent.h"
#include "components/RenderComponent.h"
#include "ui/UI.h"

RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() {}

void RenderSystem::run(District *pDistrict)
{
    for (const auto &entity : pDistrict->getEntities())
    {
        PositionComponent *positionComponent = entity->getComponent<PositionComponent>();
        TileComponent *tileComponent = entity->getComponent<TileComponent>();

        if (positionComponent && tileComponent)
        {
            auto& coords = positionComponent->currentCoordinates;
            UI::renderTile(coords.y, coords.x, tileComponent->renderColour);
        }
    }

    for (const auto &entity : pDistrict->getEntities())
    {
        PositionComponent *positionComponent = entity->getComponent<PositionComponent>();
        RenderComponent *renderComponent = entity->getComponent<RenderComponent>();

        if (positionComponent && renderComponent)
        {
            auto& coords = positionComponent->currentCoordinates;
            UI::renderEntity(coords.y, coords.x, renderComponent->renderSymbol);
        }
    }
}
