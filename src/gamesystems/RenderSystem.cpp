#include "gamesystems/RenderSystem.hpp"

#include "game/District.hpp"
#include "components/PositionComponent.hpp"
#include "components/TileComponent.hpp"
#include "components/RenderComponent.hpp"
#include "ui/UI.hpp"
#include "ui/TileColours.hpp"

int getTileColour(TileProperty::TileProperty property);

RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() {}

void RenderSystem::run(District *pDistrict)
{
    UI::renderEmptyDistrict();

    for (const auto &entity : pDistrict->getEntities())
    {
        PositionComponent *positionComponent = entity->getComponent<PositionComponent>();
        RenderComponent *renderComponent = entity->getComponent<RenderComponent>();

        if (positionComponent && renderComponent)
        {
            auto coords = positionComponent->getPosition();
            UI::renderEntity(coords, renderComponent->renderSymbol);
        }
    }

    for (const auto &entity : pDistrict->getEntities())
    {
        PositionComponent *positionComponent = entity->getComponent<PositionComponent>();
        TileComponent *tileComponent = entity->getComponent<TileComponent>();

        if (positionComponent && tileComponent)
        {
            auto coords = positionComponent->getPosition();
            auto renderColour = getTileColour(tileComponent->property);
            UI::renderTile(coords, renderColour);
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
