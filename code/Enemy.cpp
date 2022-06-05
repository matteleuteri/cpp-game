#include "Enemy.h"

// funcitons for enemy go here, like turn angle and reactionspeed
Enemy::Enemy() 
{}
Enemy::Enemy(float x, float y) : x(x), y(y)
{}

Enemy::~Enemy() 
{}

void Enemy::move(Player* player, int64_t timeElapsed) // needs time elapsed as well
{

    // NOW the player moves using x and y distance at some offset in either direction
    // LATER the player moves using an angle at some offset
    // float d = (float)tan(angle * 3.14159265358979323 / 180);

    float xDist = player->x - x;
    float yDist = player->y - y;

    x+=xDist/25;
    y+=yDist/25;

    // random noise to make movement look real
    y += (std::rand() /((RAND_MAX + 1u)/6 ));
    x += (std::rand() /((RAND_MAX + 1u)/6 ));

}
