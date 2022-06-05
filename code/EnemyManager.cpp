#include "EnemyManager.h"

void EnemyManager::spawnEnemy()
{
    

    for(int i = 0; i < sizeof(enemyList) / sizeof(Enemy*); i++)
    {
        if(enemyList[i] == nullptr)
        {
            Enemy *e = new Enemy(100, 100);
            e->bitmap = bitmap;
            enemyList[i] = e;
            break;
        }
    }
}


