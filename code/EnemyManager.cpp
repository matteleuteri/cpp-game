#include "headers/EnemyManager.h"


EnemyManager::EnemyManager(int64_t t, ID2D1Bitmap* b): lastSpawnTime(t), bitmap(b)
{
    isActive = false; // ???
    
    for(int i = 0; i < 10; ++i)
        enemyList[i] = new Enemy(100, 100, false, b);
}

void EnemyManager::spawnEnemy(int64_t endTime)
{
    for(auto& enemy: enemyList)
    {
        if(!enemy->isActive)
        {
            resetEnemy(enemy);
            break;
        }
    }
    lastSpawnTime = endTime;
}

void EnemyManager::resetEnemy(Enemy* enemy)
{
    enemy->x = 100;
    enemy->y = 100;
    enemy->isActive = true;
}