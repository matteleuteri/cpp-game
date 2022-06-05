#ifndef _ENEMY
#define _ENEMY

#include <d2d1.h>
#include <memory>

#include "Player.h"

class Enemy
{
public:
    float x;
    float y;
    float speed;
    float angle;
    ID2D1Bitmap* bitmap;
    // Enemy::Enemy(float x, float y);
    Enemy::Enemy(float x, float y);
    Enemy::Enemy();
    Enemy::~Enemy();
    void Enemy::move(Player* player, int64_t timeElapsed);
};

#endif