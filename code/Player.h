#ifndef _PLAYER
#define _PLAYER

#include <stdint.h>
#include <d2d1.h>


enum DIRECTION
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};


class Player
{
public:
    DIRECTION direction; // make a pointer?
    ID2D1Bitmap *bitmap;

    float x;
    float y;
    int width;
    int height;
    bool isActive;
    
    float leftSpeed;
    float rightSpeed;
    float upSpeed;
    float downSpeed;
    
    bool goingRight;
    bool goingLeft;
    bool goingUp;
    bool goingDown;
    void Player::updatePlayer(int64_t timeElapsed);
    void Player::moveTowardsZero(DIRECTION direction);   
};


#endif