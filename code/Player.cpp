#include "Player.h"

// these could be done with switch cases
void Player::speedUp(DIRECTION direction)
{
    if(direction == RIGHT)
    {
        goingRight = true; 
    }
    else if(direction == LEFT)
    {
        goingLeft = true;
    }
    else if(direction == UP)
    {
        goingUp = true;    
    }
    else if(direction == DOWN)
    {
        goingDown = true;
    }
}

void Player::slowDown(DIRECTION direction)
{
    if(direction == RIGHT)
    {
        goingRight = false; 
    }
    else if(direction == LEFT)
    {
        goingLeft = false;
    }
    else if(direction == UP)
    {
        goingUp = false;    
    }
    else if(direction == DOWN)
    {
        goingDown = false;
    }
}




void Player::moveTowardsZeroX() 
{
    if(xSpeed == 0) return;
    else if(xSpeed > 0) 
    {
        xSpeed -= 0.001;
        if(xSpeed < 0)
        {
            xSpeed = 0;
        }
    }
    else
    {
        xSpeed += 0.001;
        if(xSpeed > 0)
        {
            xSpeed =0;
        }
    }
}

void Player::moveTowardsZeroY() 
{
    if(ySpeed == 0) return;
    else if(ySpeed > 0) 
    {
        ySpeed -= 0.001;
        if(ySpeed < 0)
        {
            ySpeed = 0;
        }
    }
    else
    {
        ySpeed += 0.001;
        if(ySpeed > 0)
        {
            ySpeed =0;
        }
    }
}