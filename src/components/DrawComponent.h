#ifndef DRAWCOMPONENT_H_
#define DRAWCOMPONENT_H_

#include "components/Component.h"

struct DrawComponent : public Component
{
    DrawComponent(char drawSymbol) : drawSymbol(drawSymbol) {}

    virtual ~DrawComponent() = default;

    char drawSymbol;
};

#endif /* DRAWCOMPONENT_H_ */
