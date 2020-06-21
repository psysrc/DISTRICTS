#ifndef DRAWCOMPONENT_H_
#define DRAWCOMPONENT_H_

#include "components/Component.h"

class DrawComponent : public Component {
public:
    DrawComponent(char symbol = '?') : drawSymbol(symbol) {}
    virtual ~DrawComponent() {}

    char drawSymbol;
};

#endif /* DRAWCOMPONENT_H_ */