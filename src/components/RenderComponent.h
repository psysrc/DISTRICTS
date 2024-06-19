#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

#include "components/Component.h"

struct RenderComponent : public Component
{
    RenderComponent(){}

    virtual ~RenderComponent() = default;

    char renderSymbol;
};

#endif /* RENDER_COMPONENT_H_ */
