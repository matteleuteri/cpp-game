#include "headers/PauseButton.h"

void PauseButton::execute(Player* player)
{
    player->isActive = !player->isActive;
}
