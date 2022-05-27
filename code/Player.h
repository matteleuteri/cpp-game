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
    DIRECTION direction;
    int x;
    int y;
    int width;
    int height;
    float xSpeed;
    float ySpeed;
    bool isAccX;
    bool isAccY;
    bool isActive;
};


#endif