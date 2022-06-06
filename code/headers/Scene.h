#ifndef _SCENE
#define _SCENE

#define PI 3.141592653589793238463f

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
#include "Animator.h"

class Scene
{
public:
    std::vector<Projectile> projectiles;

    std::unique_ptr<Player> player;
    std::unique_ptr<EnemyManager> enemyManager;
    std::unique_ptr<Animator> animator;

    bool isActive;

    Scene::Scene(RECT* rc, HWND hwnd);
    Scene::~Scene();
    void Scene::drawPlayer(ID2D1HwndRenderTarget* renderTarget);
    void Scene::drawProjectiles(ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brush);

    void Scene::assignBitmaps(ID2D1Bitmap *playerBitmap, ID2D1Bitmap *enemyBitmap);
    void Scene::drawEnemies(ID2D1HwndRenderTarget* renderTarget);
    void Scene::updateState(HWND hwnd, int64_t startTime, int64_t endTime); 
    void Scene::updateProjectiles(int64_t timeElapsed);
    void Scene::renderState(RECT* rc, HWND hwnd, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3]);
    void Scene::renderGrid(RECT* rc, ID2D1HwndRenderTarget* renderTarget, ID2D1SolidColorBrush* brushes[3]);
};

#endif