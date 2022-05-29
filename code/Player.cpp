#include "Player.h"

void Player::moveTowardsZeroRight() 
{
    if(rightSpeed == 0) return;
    else if(rightSpeed > 0) 
    {
        rightSpeed -= 0.05;
        if(rightSpeed < 0)
        {
            rightSpeed = 0;
        }
    }
}
void Player::moveTowardsZeroLeft() 
{
    if(leftSpeed == 0) return;
    else if(leftSpeed > 0) 
    {
        leftSpeed -= 0.05;
        if(leftSpeed < 0)
        {
            leftSpeed = 0;
        }
    }
}

void Player::moveTowardsZeroUp() 
{
    if(upSpeed == 0) return;
    else if(upSpeed > 0) 
    {
        upSpeed -= 0.05;
        if(upSpeed < 0)
        {
            upSpeed = 0;
        }
    }
}

void Player::moveTowardsZeroDown() 
{
    if(downSpeed == 0) return;
    else if(downSpeed > 0) 
    {
        downSpeed -= 0.05;
        if(downSpeed < 0)
        {
            downSpeed = 0;
        }
    }
}