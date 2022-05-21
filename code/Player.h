enum DIRECTION
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};


struct Player
{
    DIRECTION direction;
    int x;
    int y;
    int width;
    int height;
    float xSpeed;
    float ySpeed;
    bool isActive;
};


