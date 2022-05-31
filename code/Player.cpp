#include "Player.h"

void Player::moveTowardsZero(DIRECTION direction) 
{
    float* dirSpeed = 0;

    if(direction == UP) dirSpeed = &upSpeed;
    else if(direction == DOWN) dirSpeed = &downSpeed;
    else if(direction == LEFT) dirSpeed = &leftSpeed;
    else if(direction == RIGHT) dirSpeed = &rightSpeed;

    if(*dirSpeed == 0) return;
    
    if(*dirSpeed > 0) 
    {
        *dirSpeed -= 0.01;
        if(*dirSpeed < 0)
        {
            *dirSpeed = 0;
        }
    }

}