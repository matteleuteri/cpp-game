#include "headers/Player.h"

void Player::moveTowardsZero(DIRECTION direction) 
{
    float* dirSpeed = 0;

    if(direction == UP)         dirSpeed = &upSpeed;
    else if(direction == DOWN)  dirSpeed = &downSpeed;
    else if(direction == LEFT)  dirSpeed = &leftSpeed;
    else if(direction == RIGHT) dirSpeed = &rightSpeed;

    if(*dirSpeed == 0) return;
    
    if(*dirSpeed > 0) 
    {
        *dirSpeed -= 0.01f;
        if(*dirSpeed < 0) *dirSpeed = 0;
    }
}

void Player::updatePlayer(int64_t timeElapsed, HWND hwnd)
{
    POINT mousePosition;
    BOOL cursorFound = GetCursorPos(&mousePosition);
    BOOL converted = ScreenToClient(hwnd, &mousePosition);
    if(cursorFound && converted) pointPlayerTowards(mousePosition);

    if(goingRight)
    {
        rightSpeed += 0.025f;
        if(rightSpeed > 1.0) // do these ones need f annotation for float?
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

    x += (rightSpeed * speedScale * (timeElapsed / 25000));
    x -= (leftSpeed  * speedScale * (timeElapsed / 25000));

    y += (downSpeed  * speedScale * (timeElapsed / 25000));
    y -= (upSpeed  * speedScale * (timeElapsed / 25000));

    if(x > 1280)    x = 0;
    else if(x < 0)  x = 1280;

    if(y > 720)     y = 0;
    else if(y < 0)  y = 720;
}


void Player::pointPlayerTowards(POINT mousePosition)
{
    float xDistance = (mousePosition.x) - (x);
    float yDistance = (mousePosition.y) - (y);
    angle = ((float)atan(yDistance / xDistance) * (180.0f /PI )) + 90.0f; // offset needed to define origin rotation angle 

    if(mousePosition.x < x) angle += 180; // not sure why, but this is important
}

Player::Player(ID2D1Bitmap *bitmap): bitmap(bitmap)
{
    isActive = false;
    goingRight = false;
    goingLeft = false;
    goingUp = false;
    goingDown = false;
    x = 400;
    y = 400;
    width = 20;
    height = 20;
    speedScale = 1.0f;
    leftSpeed = 0;
    rightSpeed = 0;
    upSpeed = 0;
    downSpeed = 0;

}