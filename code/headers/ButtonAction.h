#ifndef _BUTTONACTION
#define _BUTTONACTION

#include "Scene.h"

class ButtonAction
{
public:
    // virtual ~ButtonAction();
    virtual void execute(std::unique_ptr<Scene>& scene) = 0;
};

#endif