#include "gamesystems/RenderSystem.h"

#include "game/District.h"
#include "components/PositionComponent.h"
#include "components/TileComponent.h"
#include "components/RenderComponent.h"
#include "ui/UI.h"
#include "ui/TileColours.h"

int getTileColour(TileProperty::TileProperty property);

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
            auto& coords = positionComponent->position;
            auto renderColour = getTileColour(tileComponent->property);
            UI::renderTile(coords.y, coords.x, renderColour);
        }
    }

    for (const auto &entity : pDistrict->getEntities())
    {
        PositionComponent *positionComponent = entity->getComponent<PositionComponent>();
        RenderComponent *renderComponent = entity->getComponent<RenderComponent>();

        if (positionComponent && renderComponent)
        {
            auto& coords = positionComponent->position;
            UI::renderEntity(coords.y, coords.x, renderComponent->renderSymbol);
        }
    }
}

int getTileColour(TileProperty::TileProperty property)
{
    switch (property)
	{
	case TileProperty::Plains:
		return COLOUR_PLAINS;
	case TileProperty::Stone:
		return COLOUR_STONE;
	case TileProperty::Water:
		return COLOUR_WATER;
	case TileProperty::Bridge:
		return COLOUR_BRIDGE;
	default:
		return COLOUR_UNKNOWN;
	}
}
