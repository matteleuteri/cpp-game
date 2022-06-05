#include "EnemyManager.h"

// EnemyManager::EnemyManager()
// {
//     // enemyBitmap = enemyBitmap;
// }


void EnemyManager::spawnEnemy()
{

    enemy *e = new Enemy(100, 100, enemyBitmap);        
    enemyList.push_back(e);
}



