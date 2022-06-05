#ifndef _ENEMYMANAGER
#define _ENEMYMANAGER


#include "Enemy.h"
#include <array>



class EnemyManager
{
public:
    std::array<Enemy*, 10> enemyList; // size subject to change
    ID2D1Bitmap *bitmap;
    int64_t lastSpawnTime;
    void EnemyManager::spawnEnemy(int64_t endTime);
    void EnemyManager::resetEnemy(Enemy* enemy);
    Enemy* EnemyManager::createEnemy();
};



#endif