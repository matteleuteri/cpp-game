#include "EnemyManager.h"

// EnemyManager::EnemyManager()
// {
    // lastSpawnTime = 0;
    // enemyBitmap = enemyBitmap;
// }


void EnemyManager::spawnEnemy()
{

    Enemy *e = new Enemy(100, 100);
    e->bitmap = bitmap;

    enemyList.push_back(e);
}


