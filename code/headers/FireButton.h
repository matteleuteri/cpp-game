#ifndef _FIRE_BUTTON
#define _FIRE_BUTTON

#include "ButtonAction.h"

class FireButton : public ButtonAction
{
public:
    virtual void execute(Player* player);
};

#endif