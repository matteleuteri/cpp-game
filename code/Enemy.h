#ifndef _ENEMY
#define _ENEMY

#include <d2d1.h>
#include <memory>
#include <vector>
#include "Player.h"
#include "Projectile.h"

class Enemy
{
public:
    float x;
    float y;
    float speed;
    float angle;
    ID2D1Bitmap* bitmap;
    bool isActive;
    Enemy::Enemy(float x, float y);
    Enemy::Enemy();
    
    Enemy::~Enemy();
    void Enemy::update(std::vector<Projectile> projectiles, Player* player, int64_t timeElapsed);

    void Enemy::move(Player* player, int64_t timeElapsed);
    void Enemy::detectHit(std::vector<Projectile> projectiles);
};

#endif