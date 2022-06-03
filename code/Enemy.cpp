#include "Enemy.h"


// funcitons for enemt go here, like turn angle and reactionspeed
Enemy::Enemy() 
{
}
Enemy::~Enemy() {}

void Enemy::move()
{
    x+=2;
    y+=2;
}