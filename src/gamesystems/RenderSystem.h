#ifndef RENDER_SYSTEM_H_
#define RENDER_SYSTEM_H_

#include "gamesystems/GameSystem.h"

class RenderSystem : public GameSystem
{
public:
    RenderSystem();
    virtual ~RenderSystem();
    virtual void run(District *pDistrict) override;
};

#endif /* RENDER_SYSTEM_H_ */
