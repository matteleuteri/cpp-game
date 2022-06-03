#ifndef _ENEMY
#define _ENEMY

#include <d2d1.h>
#include <memory>

class Enemy
{
public:
    float x;
    float y;
    float speed;
    float angle;
    ID2D1Bitmap* bitmap;
    Enemy::Enemy(float x, float y, ID2D1Bitmap* b);
    Enemy::Enemy(float x, float y);
    // Enemy::Enemy();
    Enemy::~Enemy();
    void Enemy::move();
};

#endif