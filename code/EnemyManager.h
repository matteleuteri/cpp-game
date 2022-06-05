#ifndef _ENEMYMANAGER
#define _ENEMYMANAGER


#include "Enemy.h"
#include <vector>


class EnemyManager
{
public:
    Enemy* enemyList[10]; // size subject to change
    ID2D1Bitmap *bitmap;
    int64_t lastSpawnTime;
    void EnemyManager::spawnEnemy();
};



#endif