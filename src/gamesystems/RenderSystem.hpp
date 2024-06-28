#ifndef RENDER_SYSTEM_H_
#define RENDER_SYSTEM_H_

#include "gamesystems/GameSystem.hpp"

class RenderSystem : public GameSystem
{
public:
    RenderSystem();
    virtual ~RenderSystem();
    virtual void run(District *) override;
};

#endif /* RENDER_SYSTEM_H_ */
