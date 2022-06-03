#include "Enemy.h"


// funcitons for enemt go here, like turn angle and reactionspeed
Enemy::Enemy(float x, float y) : x(x), y(y)
{
    // x = x;
    // y = y;
    // bitmap = bitmap;
}
Enemy::Enemy(float x, float y, ID2D1Bitmap* b) : x(x), y(y), bitmap(b)
{
    // x = x;
    // y = y;
    // bitmap = b;
}
// Enemy::Enemy() 
// {}
Enemy::~Enemy() {}

void Enemy::move()
{
    x+=2;
    y+=2;
}