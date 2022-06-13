#ifndef _STARTBUTTON
#define _STARTBUTTON

#include "ButtonAction.h"

class StartButton : public ButtonAction
{
public:
    void StartButton::execute(std::unique_ptr<Scene>& scene);
};

#endif