#include "Enemy.h"


// funcitons for enemy go here, like turn angle and reactionspeed
Enemy::Enemy() 
{}
Enemy::Enemy(float x, float y) : x(x), y(y)
{}
// Enemy::Enemy(float x, float y, ID2D1Bitmap* b) : x(x), y(y), bitmap(b)
// {}



Enemy::~Enemy() 
{}

void Enemy::move(Player* player, int64_t timeElapsed) // needs time elapsed as well
{
    // use the angle to get how much to go in either direction
    // then add random noise back and forth

    // float d = (float)tan(angle * 3.14159265358979323 / 180);
    // maybe we need to account for the flip 180 when we get the angle


    float xDist = player->x - x;
    float yDist = player->y - y;


    x+=xDist/25;
    y+=yDist/25;

    // random noise to make movement look real
    y += (std::rand() /((RAND_MAX + 1u)/6 ));
    x += (std::rand() /((RAND_MAX + 1u)/6 ));

}


// void Enemy::spawnEnemy()
// {
//     if(endTime - lastSpawnTime >= 20000000)
//     {
//         OutputDebugStringA("spwan\n");
//         lastSpawnTime = endTime;
//         Enemy *e = new Enemy(100, 100, enemyBitmap);
            
//         enemies.push_back(e);
//     }
// }