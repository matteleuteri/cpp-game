#ifndef _PLAYER
#define _PLAYER

#include <stdint.h>
#include <d2d1.h>
#include <memory>

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
    // DIRECTION direction; // make a pointer?
    ID2D1Bitmap* bitmap;

    float x;
    float y;
    float angle; 

    int width;
    int height;
    bool isActive;
    
    float leftSpeed;
    float rightSpeed;
    float upSpeed;
    float downSpeed;

    float speedScale;// speed boost modifier / scaler/ thingy
    
    bool goingRight;
    bool goingLeft;
    bool goingUp;
    bool goingDown;
    void Player::updatePlayer(int64_t timeElapsed);
    void Player::pointPlayerTowards(POINT mousePosition);
    void Player::moveTowardsZero(DIRECTION direction);   
};


#endif