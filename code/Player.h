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
    float xSpeed;
    float ySpeed;
    bool goingRight;
    bool goingLeft;
    bool goingUp;
    bool goingDown;
    bool isActive;
    void Player::speedUp(DIRECTION direction);
    void Player::slowDown(DIRECTION direction);
    void Player::moveTowardsZeroX();
    void Player::moveTowardsZeroY();
};




#endif