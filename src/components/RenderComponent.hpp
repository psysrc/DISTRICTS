#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

#include "components/Component.hpp"

struct RenderComponent : public Component
{
    RenderComponent(char symbol) : renderSymbol(symbol) {}

    virtual ~RenderComponent() = default;

    char renderSymbol;
};

#endif /* RENDER_COMPONENT_H_ */
