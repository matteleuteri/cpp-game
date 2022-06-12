#ifndef _BUTTONACTION
#define _BUTTONACTION

#include "Player.h"

class ButtonAction
{
public:
    // virtual ~ButtonAction();
    virtual void execute(Player* player) = 0;
};

#endif