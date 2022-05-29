#ifndef _PLAYER
#define _PLAYER

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
    int x;
    int y;
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

    void Player::moveTowardsZeroUp();
    void Player::moveTowardsZeroDown();
    void Player::moveTowardsZeroLeft();
    void Player::moveTowardsZeroRight();    
};


#endif