#include "headers/Mountain.h"

Mountain::Mountain(ID2D1Bitmap* b, float x, float y): bitmap(b), x(x), y(y)
{}

void Mountain::update(Player* player, int64_t timeElapsed) 
{
    if(player->goingDown && y < yMax)
    {
        y += (player->downSpeed * timeElapsed/ 25000);
    }
    if(player->goingUp && y > yMin)
    {
        y -= (player->upSpeed * timeElapsed/ 25000);
    }
    if(player->goingLeft && x > xMin)
    {
        x -= (player->leftSpeed * timeElapsed/ 25000);
    }
    if(player->goingRight && x < xMax)
    {
        x += (player->rightSpeed * timeElapsed/ 25000);
    }
}