#ifndef _ENEMYMANAGER
#define _ENEMYMANAGER


#include "Enemy.h"
#include <vector>


class EnemyManager
{
public:
    std::vector<Enemy*> enemyList;
    ID2D1Bitmap *bitmap;
    int64_t lastSpawnTime;
    
    void EnemyManager::spawnEnemy();

};



#endif