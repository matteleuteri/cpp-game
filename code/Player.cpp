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
        *dirSpeed -= 0.01f;
        if(*dirSpeed < 0)
        {
            *dirSpeed = 0;
        }
    }

}

void Player::updatePlayer(int64_t timeElapsed)
{
    if(goingRight)
    {
        rightSpeed += 0.025f;
        if(rightSpeed > 1.0) // do these ones neede f annotation for float?
        {
            rightSpeed = 1.0;
        }
    }
    else moveTowardsZero(RIGHT);


    if(goingLeft)
    {
        (leftSpeed) += 0.025f;
        if(leftSpeed > 1.0)
        {
            leftSpeed = 1.0;
        }
    }
    else moveTowardsZero(LEFT);


    if(goingDown)
    {
        (downSpeed) += 0.025f;
        if(downSpeed > 1.0)
        {
            downSpeed = 1.0;
        }
    }
    else moveTowardsZero(DOWN);


    if(goingUp)
    {
        (upSpeed) += 0.025f;
        if(upSpeed > 1.0)
        {
            upSpeed = 1.0;
        }
    }
    else moveTowardsZero(UP);


    x += (rightSpeed* (timeElapsed / 25000));
    x -= (leftSpeed * (timeElapsed / 25000));

    y += (downSpeed * (timeElapsed / 25000));
    y -= (upSpeed * (timeElapsed / 25000));

    if(x > 1280)    x = 0;
    else if(x < 0)  x = 1280;

    if(y > 720)     y = 0;
    else if(y < 0)  y = 720;

}