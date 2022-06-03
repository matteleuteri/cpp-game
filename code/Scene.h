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
#include "Enemy.h"


class Scene
{
public:
    std::unique_ptr<Player> player;
    std::vector<Projectile> projectiles;
    std::vector<Enemy*> enemies;

    int64_t lastSpawnTime = 0;
    bool isActive;

    ID2D1SolidColorBrush* brushes[3];
    ID2D1HwndRenderTarget* renderTarget;
    ID2D1Bitmap *playerBitmap;
    ID2D1Bitmap *enemyBitmap;
    
    Scene::Scene(RECT* rc, HWND hwnd);
    Scene::~Scene();
    void Scene::drawEnemies();
    void Scene::updateState(int64_t startTime, int64_t endTime);
    void Scene::updateProjectiles(int64_t timeElapsed);
    void Scene::renderState(RECT* rc, HWND hwnd);
    void Scene::createResources(HWND hwnd, RECT* rc);
    void Scene::renderGrid(RECT* rc);
    void Scene::pointPlayerTowards(POINT mousePosition);
    HRESULT Scene::LoadBitmapFromFile(IWICImagingFactory *pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap);
};

#endif