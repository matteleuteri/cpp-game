#ifndef _ENEMY
#define _ENEMY

#include <d2d1.h>
#include <memory>
#include <vector>
#include "Player.h"
#include "Projectile.h"
#include "Animator.h"

class Enemy
{
public:
    float x;
    float y;
    float speed;
    float angle;
    ID2D1Bitmap* bitmap;
    bool isActive;
    Enemy::Enemy(float x, float y, bool ia, ID2D1Bitmap* b);
    Enemy::Enemy();


    void Enemy::update(std::vector<Projectile> projectiles, Player* player, Animator* animator, int64_t timeElapsed, int64_t currTime);
    void Enemy::move(Player* player, int64_t timeElapsed);
    void Enemy::detectHit(std::vector<Projectile> projectiles, Animator* animator, int64_t t);
    void Enemy::draw(ID2D1HwndRenderTarget* renderTarget, Player* player);
};

#endif