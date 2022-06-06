#include "headers/Enemy.h"

// funcitons for enemy go here, like turn angle and reactionspeed
Enemy::Enemy() 
{
    isActive = true;
}

Enemy::Enemy(float x, float y) : x(x), y(y)
{}

Enemy::~Enemy() 
{}

void Enemy::move(Player* player, int64_t timeElapsed) // needs time elapsed as well
{
    //TODO
    // NOW the player moves using x and y distance at some offset in either direction
    // LATER the player moves using an angle at some offset
    // float d = (float)tan(angle * 3.14159265358979323 / 180);

    float xDist = player->x - x;
    float yDist = player->y - y;

    x += xDist/50;
    y += yDist/50;

    // random noise to make movement look real
    // y += (std::rand() / ((RAND_MAX + 1u) / 6));
    // x += (std::rand() / ((RAND_MAX + 1u) / 6));

}

void Enemy::detectHit(std::vector<Projectile> projectiles, Animator* animator)
{
    for(Projectile& p : projectiles)
    {
        if(std::abs(p.x - x) < 20 && std::abs(p.y - y) < 20)
        {
            OutputDebugStringA("hit!\n");
            // play explosion animation, and mark as to delete, and glow grid lines
            isActive = false;
            // animator->col = x;
            // animator->row = y;// thse two lines mark an explosion
        }
    } 
}


void Enemy::update(std::vector<Projectile> projectiles, Player* player, Animator* animator, int64_t timeElapsed)
{
    move(player, timeElapsed);
    detectHit(projectiles, animator);
}
