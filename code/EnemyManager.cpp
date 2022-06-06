#include "headers/EnemyManager.h"

void EnemyManager::spawnEnemy(int64_t endTime)
{
    for(auto& enemy: enemyList)
    {
        if(enemy == nullptr)
        {
            enemy = createEnemy();
            break;
        }
        if(!enemy->isActive)
        {
            resetEnemy(enemy);
            break;
        }
    }
    lastSpawnTime = endTime;
}

Enemy* EnemyManager::createEnemy()
{
    Enemy *e = new Enemy(100, 100);
    e->bitmap = bitmap;
    return e;
}

void EnemyManager::resetEnemy(Enemy* enemy)
{
    enemy->x = 100;
    enemy->y = 100;
    enemy->isActive = true;
}

// EnemyManager::EnemyManager(int64_t l)
// {
//     lastSpawnTime = l;
// }
