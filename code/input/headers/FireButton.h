#ifndef _FIREBUTTON
#define _FIREBUTTON

#include "ButtonAction.h"

class FireButton : public ButtonAction
{
public:
    virtual void execute(std::unique_ptr<Scene>& scene);
};

#endif