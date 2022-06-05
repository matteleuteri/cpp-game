#ifndef _SCENE
#define _SCENE

#include <windows.h>
#include <stdint.h>
#include <d2d1.h>
#include <vector>
#include <memory>
#include <wincodec.h>
#include <combaseapi.h>
#include <Objbase.h>

#include "Player.h"
#include "Projectile.h"
#include "EnemyManager.h"

class Scene
{
public:
    std::unique_ptr<Player> player;
    std::vector<Projectile> projectiles;
    // std::vector<Enemy*> enemies;
    std::unique_ptr<EnemyManager> enemyManager;

    int64_t lastSpawnTime = 0;
    bool isActive;

    Scene::Scene(RECT* rc, HWND hwnd);
    Scene::~Scene();
    void Scene::drawEnemies(ID2D1HwndRenderTarget* renderTarget);
    void Scene::updateState(int64_t startTime, int64_t endTime); 
    void Scene::updateProjectiles(int64_t timeElapsed);
    void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3]);
    void Scene::renderGrid(RECT* rc, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3]);
};

#endif