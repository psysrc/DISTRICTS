#ifndef RENDER_SYSTEM_H_
#define RENDER_SYSTEM_H_

#include "gamesystems/GameSystem.hpp"

/**
 * Handles the rendering of the whole district to the UI.
 */
class RenderSystem : public GameSystem
{
public:
    RenderSystem();
    virtual ~RenderSystem();
    virtual void run(District *) override;
};

#endif /* RENDER_SYSTEM_H_ */
