#ifndef _ENEMY
#define _ENEMY

#include <d2d1.h>
#include <memory>

class Enemy
{
public:
    float x;
    float y;
    ID2D1Bitmap* bitmap;

    Enemy::Enemy();
    Enemy::~Enemy();
    void Enemy::move();
};

#endif