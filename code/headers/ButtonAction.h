#ifndef _BUTTON_ACTION
#define _BUTTON_ACTION

#include "Player.h"

class ButtonAction
{
public:
    // virtual ~ButtonAction();
    virtual void execute(Player* player) = 0;
};

#endif